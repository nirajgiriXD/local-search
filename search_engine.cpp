#include <iostream>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

void permutation(const int start, int last, string str){
    ifstream dic;
    dic.open("Dic.txt");
    if(!dic.is_open()){
        cout << "Error: Cannot open file";
        exit(1);
    }
    char temp;
    string dicWord;
    int i, j, limit=3, index=0, lengthDicWord, lengthSearchQuery = str.length();
    for(i = start; i < last-1; ++i){
        for(j = i+1; j < last; ++j){
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            permutation(i+1 ,last, str);
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
    }
    dic.seekg(0, ios::beg);
    while(dic >> dicWord){
        lengthDicWord = dicWord.length();
        transform(dicWord.begin(), dicWord.end(), dicWord.begin(), ::tolower);
        if(lengthDicWord < lengthSearchQuery+limit){
            if((dicWord.find(str))!=(-1)){
                cout << "-> " << dicWord << "\n\t";
            }
        }
    }
    dic.close();
}

//For search_query.length>=3
void didUmean(string search_query){
    transform(search_query.begin(), search_query.end(), search_query.begin(), ::tolower);
    int i, j, pos, flag=0, indexPri0=0, indexPri1=0, indexPri2=0, iniSubStrSize, maxDicWordSize, lengthDicWord, lengthSearchQuery = search_query.length();
    string dicWord, priority0[8], priority1[13], priority2[89];
    char opt;
    ifstream dic;
    dic.open("Dic.txt");
    if(!dic.is_open()){
        cout << "Error: Cannot open file";
        exit(1);
    }
    //Initializing Length of Substring
    if(lengthSearchQuery<5){
        iniSubStrSize = 3;
        maxDicWordSize = 7;
    }
    else if(lengthSearchQuery>=5 && lengthSearchQuery<=10){
        iniSubStrSize = 4;
        maxDicWordSize = 45;
    }
    else{
        iniSubStrSize = 5;
        maxDicWordSize = 45;
    }
    //File Reading and Checking
    dic.seekg(0, ios::beg);
    while(dic >> dicWord){
        transform(dicWord.begin(), dicWord.end(), dicWord.begin(), ::tolower);
        lengthDicWord = dicWord.length();
        if(lengthDicWord>=iniSubStrSize && lengthDicWord<=maxDicWordSize){
            for(i=0; i<lengthSearchQuery-iniSubStrSize+1; i++){
                pos = dicWord.find(search_query.substr(i, i+iniSubStrSize));
                if(pos!=(-1)){
                    if(pos==0 && (search_query[0]==dicWord[0])){
                        priority0[indexPri0++] = dicWord;
                        break;
                    }
                    else if((lengthDicWord-pos)==lengthSearchQuery){
                        priority1[indexPri1++] = dicWord;
                        break;
                    }
                    else{
                        priority2[indexPri2++] = dicWord;
                        break;
                    }
                }
            }
        }
    }
    //Finding Best Result:
    cout << "\n\n\t\t\tQuery Not Found: " << search_query << endl << endl;
    if(indexPri0>0 || indexPri1>0){
        if(indexPri0==1){
            cout << "\n\tDid you mean: " << priority0[0] << "\n\t";
        }
        else{
            cout << "\n\tDid you mean: (any of these below)" << "\n\n\t";
            for(i=0; i<indexPri0; i++){
                cout << "-> " << priority0[i] << "\n\t";
            }
            for(i=0; i<indexPri1; i++){
                cout << "-> " << priority1[i] << "\n\t";
            }
        }
    }
    cout << "\n\tSuggestions(Y/N): ";
    cin >> opt;
    if(opt=='Y' || opt=='y'){
        cout << "\n\t";
        if(lengthSearchQuery<5){
            permutation(0, lengthSearchQuery, search_query);
            cout << "\n\t";
        }
        if(indexPri2>0){
            for(i=0; i<indexPri2; i++){
                cout << "-> " << priority2[i] << "\n\t";
            }
        }
    }
    cout << "\n\t";
    dic.close();
}

//For search_query.length()=1
void didUmean1(string search_query){
    transform(search_query.begin(), search_query.end(), search_query.begin(), ::tolower);
    int i, pos, limit=4, indexPri1=0, indexPri2=0, indexPri3=0, lengthDicWord;
    string dicWord, priority1[13], priority2[21], priority3[55];
    char opt;
    cout << "\n\n\t\t\tQuery Found: " << search_query << endl << endl;
    if((search_query[0]>='a' && search_query[0]<='z') || (search_query[0]>='A' && search_query[0]<='Z')){
        cout << "\n\t" << search_query << ":\n\t";
        cout << search_query << " is an English alphabet." << endl;
    }
    else if(search_query[0]>='0' && search_query[0]<='9'){
        cout << "\n\t" << search_query << ":\n\t";
        cout << search_query << " is a mathematical notation for representing number." << endl;
    }
    else{
        cout << "\n\t" << search_query << "\n\t";
        cout << search_query << " is a special character." << endl;
    }
    if(search_query>="a" && search_query<="z"){
        ifstream dic;
        dic.open("Dic.txt");
        if(!dic.is_open()){
            cout << "Error: Cannot open file";
            exit(1);
        }
        dic.seekg(0, ios::beg);
        while(dic >> dicWord){
            lengthDicWord = dicWord.length();
            if(lengthDicWord<=limit){
                pos = dicWord.find(search_query);
                if(pos==0){
                    if(lengthDicWord==2){
                        priority1[indexPri1++] = dicWord;
                    }
                    else if(lengthDicWord==3){
                        priority2[indexPri2++] = dicWord;
                    }
                    else if(lengthDicWord==4){
                        priority3[indexPri3++] = dicWord;
                    }
                }
            }
        }
        cout << "\n\tSuggestions(Y/N): ";
        cin >> opt;
        if(opt=='Y' || opt=='y'){
            cout << "\n\t";
            for(i=0; i<indexPri1; i++){
                cout << "-> " << priority1[i] << "\n\t";
            }
            for(i=0; i<indexPri2; i++){
                cout << "-> " << priority2[i] << "\n\t";
            }
            for(i=0; i<indexPri3; i++){
                cout << "-> " << priority3[i] << "\n\t";
            }
        }
        dic.close();
    }
    cout << "\n\t";
}

//For search_query.length()=2
void didUmean2(string search_query){
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string dicWord, priority0[3], priority1[3], priority2[13], priority3[21], tem1, tem2;
    string revStr = search_query;
    reverse(revStr.begin(), revStr.end());;
    int i, j, pos, flag=0, limit=6, indexPri0=0, indexPri1=0, indexPri2=0, indexPri3=0, lengthDicWord, lengthSearchQuery=search_query.length();
    char opt;
    ifstream dic;
    dic.open("Dic.txt");
    if(!dic.is_open()){
        cout << "Error: Cannot open file";
        exit(1);
    }
    tem1 = search_query[0];
    tem2 = search_query[1];
    dic.seekg(0, ios::beg);
    cout << "\n\n\t\t\tQuery Not Found: " << search_query << endl << endl;
    while(dic >> dicWord){
        transform(dicWord.begin(), dicWord.end(), dicWord.begin(), ::tolower);
        lengthDicWord = dicWord.length();
        if(lengthDicWord==lengthSearchQuery){
            if((dicWord.find(tem1))==0){
                priority0[indexPri0++] = dicWord;
            }
            else if((dicWord.find(tem2))==1){
                priority1[indexPri1++] = dicWord;
            }
            else if((dicWord.find(revStr))!=(-1)){
                priority1[indexPri1++] = dicWord;
            }
        }
        else if(lengthDicWord>2 && lengthDicWord<limit){
            for(i=0; i<lengthDicWord ; i++){
                pos = dicWord.find(search_query);
                if(pos!=(-1)){
                    if(pos==0 || (lengthDicWord-pos)==lengthSearchQuery){
                        priority2[indexPri2++] = dicWord;
                        break;
                    }
                    else{
                        priority3[indexPri3++] = dicWord;
                        break;
                    }
                }
            }
        }
    }
    if(indexPri1>0 || indexPri0>0){
        if(indexPri1==0 && indexPri0==1){
            cout << "\n\tDid you mean: " << priority0[0] << "\n\t";
        }
        else if(indexPri0==0 && indexPri1==1){
            cout << "\n\tDid you mean: " << priority1[0] << "\n\t";
        }
        else{
            cout << "\n\tDid you mean: (any of these below)" << "\n\n\t";
            for(i=0; i<indexPri0; i++){
                cout << "-> " << priority0[i] << "\n\t";
            }
            for(i=0; i<indexPri1; i++){
                cout << "-> " << priority1[i] << "\n\t";
            }
        }
    }
    cout << "\n\tSuggestions(Y/N): ";
    cin >> opt;
    if(opt=='Y' || opt=='y'){
        if(indexPri2>0 || indexPri3>0){
            cout << "\n\t";
            for(i=0; i<indexPri2; i++){
                cout << "-> " << priority2[i] << "\n\t";
            }
            for(i=0; i<indexPri3; i++){
                cout << "-> " << priority3[i] << "\n\t";
            }
        }
    }
    cout << "\n\t";
    dic.close();
}

int main(){
    char search_query[45], dicWord[45], choice, tem[45], def[500];
    string definition;
    bool flag=0, found=0;
    int lengthSearchQuery;
g1:
    ifstream dic;
    dic.open("Dic.txt");
    if(!dic.is_open()){
        cout << "Error: Cannot open file";
        exit(1);
    }
    system("cls");
    cout << "\n\n\t\t\t  Search Engine\n\n";
    cout << "\tEnter your query: ";
    cin >> search_query;
    lengthSearchQuery = strlen(search_query);
    system("cls");
    if(lengthSearchQuery>1){
        while(dic >> dicWord){
            if((strcmpi(search_query,dicWord))==0){
                cout << "\n\n\t\t\tQuery Found: " << search_query << endl << endl;
                cout << "\n\t" << search_query << ":\n\t";
                cout << "The search query is in our database; definition not available.\n\n\t";
                goto g2;
                break;
            }
        }
    }
    if(lengthSearchQuery==1){
        didUmean1(search_query);
    }
    else if(lengthSearchQuery==2){
        didUmean2(search_query);
    }
    else{
        didUmean(search_query);
    }
g2:
    dic.close();
    cout << "Search Again(Y/N): ";
    cin >> choice;
    if(choice=='Y' || choice=='y'){
        goto g1;
    }
    else{
        cout << endl;
        exit(0);
    }
    return 0;
}
