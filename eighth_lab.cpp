#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <math.h>
using std::cin;
using std::swap;
using std::endl;
                               
std::string toLowerCase(const std::string& str) { // за идею спасибо Дане Рябчунову
    std::string low_str;
    low_str.reserve(str.size()); // предварительное выделение памяти

    for (char ch : str) {
        low_str += std::tolower(ch); // преобразуем каждый символ в строчную букву
    }

    return low_str;
}
void task1(){
    std::ifstream File("text.txt"); // открыли выходной поток файла

    std::string text((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>()); // считали его

    File.close(); // закрыли поток

    std::vector<std::string> words; // вектор со всеми словами из файла

    std::istringstream iss(text); // создаем поток из строки

    std::string word; // строка для выгрузки слов из потока
    while (iss >> word) { // извлекаем слова из потока
        const std::string punctuation = ".,!?;:()";
        std::string result;
        if (std::find(words.begin(), words.end(), word) != words.end()) continue;
        for (char symb : word) {
            // если символ не является знаком препинания, добавляем его в результат
            if (punctuation.find(symb) == std::string::npos) {
                result += symb;
            }
        }
        words.push_back(toLowerCase(result)); // переводим в нижний регистр и добавляем каждое слово в вектор
    }
    
    std::vector<std::string> good_words; // вектор для слов, удовлетворяющих условию
    std::string consonants = "bcdfghjklmnpqrstvwxyz";
    for (int i = 0; i < words.size(); i++){
        std::vector<char> cur_consonants; // вектор для согласных конкретного слова
        for (int j = 0; j < words[i].size(); j++){
            if (std::find(cur_consonants.begin(), cur_consonants.end(), words[i][j]) == cur_consonants.end()) continue; // если такая согласная уже была, то пропускаем
            if (std::find(consonants.begin(), consonants.end(), words[i][j]) == consonants.end()) cur_consonants.push_back(words[i][j]); // если такая согласная не была, то добавляем
        }
        if (std::find(good_words.begin(), good_words.end(), words[i]) == good_words.end()) good_words.push_back(words[i]); // если слово не дубликат, то добавляем
    }

    std::sort(good_words.begin(), good_words.end(), [](std::string a, std::string b){return a.size() > b.size();}); // сортируем по длине слова

    std::ofstream File2("change_text.txt"); // открыли выходный поток файла
    int count = 2000; // не больше 2000 слов по условию
    for (int i = 0; i < good_words.size(); i++){
        if (i > count) break;
        File2 << good_words[i] << " "; // записываем в файл
        std::cout << good_words[i] << " ";
    }
}
bool isTextWithPalsCheck(std::vector<std::string> text){
    int count = 0; // счетчик непалиндромов
    for (int i = 0; i < text.size(); i++){
        bool isPal = true;
        int len = text[i].length(); // считываем длину слова
        if (text[i].length() > 1) {
            for(int i = 0; i < len/2; ++i)
	        {
		        if(text[i] != text[len-i-1]) // если отзеркаленные символы не равны, значит слово не палиндром
		        {
			        isPal = false;
                    break;
		        }
	        }
            if (!isPal) count++;
        }
    }
    if (count == text.size()) return false; // если количество слов, не являющиеся палиндромами, равно количеству слов, то текст не содержит палиндромов
    return true;
}
int consonantsCount(std::string word){ // подсчёт согласных
    std::string consonants = "bcdfghjklmnpqrstvwxyz";
    int count = 0;
    for (int i = 0; i < word.length(); i++){
        if (std::find(consonants.begin(), consonants.end(), word[i]) != consonants.end()) count++; // если буква согласная, увеличиваем счётчик
    }
    return count;
}
void task2(){
    std::ifstream File; // открыли выходной поток файла
    File.open("text.txt");

    std::string text((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>()); // считали его

    File.close(); // закрыли поток

    std::vector<std::string> words; // вектор со всеми словами

    std::istringstream iss(text); // создаем поток из строки

    std::string word; // строка для выгрузки слов из потока
    while (iss >> word) { // извлекаем слова из потока
        const std::string punctuation = ".,!?;:()";
        std::string result;
        for (char symb : word) {
            // если символ не является знаком препинания, добавляем его в результат
            if (punctuation.find(symb) == std::string::npos) {
                result += symb;
            }
        }
        words.push_back(toLowerCase(result)); // переводим в нижний регистр и добавляем каждое слово в вектор
    }

    if (!isTextWithPalsCheck(words)){
        std::sort(words.begin(), words.end(), [](std::string a, std::string b){return consonantsCount(a) > consonantsCount(b);}); // сортируем по кол-ву согласных
        for (int i = 0; i < words.size(); i++){
            std::cout << words[i] << " ";
        }
    } 
    else {
        std::vector<std::string> without_vowels_text; // вектор для слов без гласных
        for (int i = 0; i < words.size(); i++){
            const std::string vowels = "aeiouy"; // строка с гласными буквами
            std::string result2;
            for (char symb : words[i]) {
                // если символ не является гласной буквой, добавляем его в результат
                if (vowels.find(symb) == std::string::npos) {
                    result2 += symb;
                }
            }
            without_vowels_text.push_back(result2); // переводим в нижний регистр и добавляем каждое слово в вектор
        }

        std::sort(without_vowels_text.begin(), without_vowels_text.end(), [](std::string a, std::string b){return a[0] > b[0];}); 

        for (int i = 0; i < without_vowels_text.size(); i++){
            std::cout << without_vowels_text[i] << " ";
        }
    }
}

void task3(){
    std::ifstream File("input.txt"); // открыли выходной поток файла

    std::string text((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>()); // считали его

    File.close(); // закрыли поток

    std::vector<std::string> words; // вектор со всеми словами

    std::istringstream iss(text); // создаем поток из строки

    std::string word; // строка для выгрузки слов из потока
    while (iss >> word) { // извлекаем слова из потока
        const std::string punctuation = ".,!?;:()";
        std::string result;
        for (char symb : word) {
            // если символ не является знаком препинания, добавляем его в результат
            if (punctuation.find(symb) == std::string::npos) {
                result += symb;
            }
        }
        words.push_back(toLowerCase(result)); // переводим в нижний регистр и добавляем каждое слово в вектор
    }

    std::vector<std::string> good_words; // вектор для слов, удовлетворяющих условию
    std::vector<std::string> val_of_vowels; // вектор с гласными буквами для каждого слова
    for (int i = 0; i < words.size(); i++){
        const std::string vowels = "aeiouy"; // строка с гласными буквами
        int count_vowels = 0; // счетчик гласных букв в конкретном слове
        std::string found_vowels; // строка с гласными в конкретном слове
        for (char symb : words[i]) {
            // если символ является гласной буквой и не дубликат, увеличиваем счетчик и прибавляем значение в строку с гласными
            if (vowels.find(symb) != std::string::npos && std::find(found_vowels.begin(), found_vowels.end(), symb) == found_vowels.end()) {
                count_vowels++;
                found_vowels += symb;
            }   
        }
        words[i][0] = toupper(words[i][0]); // первеводим первую букву слова в верхний регистр
        if (count_vowels > 3 && std::find(good_words.begin(), good_words.end(), words[i]) == good_words.end()){ // если слово удовлетворяет условию и не дубликат
            val_of_vowels.push_back(found_vowels);
            good_words.push_back(words[i]); // добавляем каждое слово в вектор
        }
    }

    std::ofstream File2("output.txt"); // открыли выходной поток файла
    for (int i = 0; i < good_words.size(); i++){
        File2 << good_words[i] << " (" << val_of_vowels[i] << ") " << endl; // записываем в файл согласно условию
        std::cout << good_words[i] << " (" << val_of_vowels[i] << ") " << endl;
    }
}

int main() {
    // varian 7
    task1();
    //task2();
    //task3();
}
