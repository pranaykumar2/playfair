#include <stdio.h>
#include <string.h>

char list1[] = "abcdefghiklmnopqrstuvwxyz";

void removeSpaces(char* str) {
   int count = 0;
   for (int i = 0; str[i]; i++) {
       if (str[i] != ' ') {
           str[count++] = str[i];
       }
   }
   str[count] = '\0';
}

void toLowerCase(char* str) {
   for (int i = 0; str[i]; i++) {
       if (str[i] >= 'A' && str[i] <= 'Z') {
           str[i] = str[i] + 32;
       }
   }
}

void fillDiagraph(char* str) {
   int len = strlen(str);
   for (int i = 0; i < len; i += 2) {
       if (str[i] == str[i + 1]) {
           for (int j = len; j > i + 1; j--) {
               str[j] = str[j - 1];
           }
           str[i + 1] = 'z';
           str[len + 1] = '\0';
           len++;
       }
   }
}

void generateKeyTable(char* key, char* table) {
   int len = strlen(key);
   int index = 0;
   for (int i = 0; i < len; i++) {
       int flag = 0;
       for (int j = 0; j < index; j++) {
           if (key[i] == table[j]) {
               flag = 1;
               break;
           }
       }
       if (flag == 0) {
           table[index++] = key[i];
       }
   }
   for (int i = 0; i < 26; i++) {
       int flag = 0;
       for (int j = 0; j < index; j++) {
           if (list1[i] == table[j]) {
               flag = 1;
               break;
           }
       }
       if (flag == 0) {
           table[index++] = list1[i];
       }
   }
   table[index] = '\0';
}

void encryptByPlayfairCipher(char* table, char* plainText, char* cipherText) {
   int len = strlen(plainText);
   for (int i = 0; i < len; i += 2) {
       int row1, col1, row2, col2;
       for (int j = 0; j < 5; j++) {
           for (int k = 0; k < 5; k++) {
               if (table[j * 5 + k] == plainText[i]) {
                  row1 = j;
                  col1 = k;
               }
               if (table[j * 5 + k] == plainText[i + 1]) {
                  row2 = j;
                  col2 = k;
               }
           }
       }
       if (row1 == row2) {
           cipherText[i] = table[row1 * 5 + (col1 + 1) % 5];
           cipherText[i + 1] = table[row2 * 5 + (col2 + 1) % 5];
       } else if (col1 == col2) {
           cipherText[i] = table[((row1 + 1) % 5) * 5 + col1];
           cipherText[i + 1] = table[((row2 + 1) % 5) * 5 + col2];
       } else {
           cipherText[i] = table[row1 * 5 + col2];
           cipherText[i + 1] = table[row2 * 5 + col1];
       }
   }
   cipherText[len] = '\0';
}

void printMatrix(char* table) {
   for (int i = 0; i < 5; i++) {
       for (int j = 0; j < 5; j++) {
           printf("%c ", table[i * 5 + j]);
       }
       printf("\n");
   }
}

int main() {
   char text_Plain[100];
   char key[100];

   printf("Enter the plain text: ");
   scanf(" %s", text_Plain);

   printf("Enter the key: ");
   scanf(" %s", key);

   removeSpaces(text_Plain);
   toLowerCase(text_Plain);
   fillDiagraph(text_Plain);

   printf("Key text: %s\n", key);
   toLowerCase(key);

   char Matrix[26];
   generateKeyTable(key, Matrix);

   printf("Plain Text: %s\n", text_Plain);

   char CipherText[100];
   encryptByPlayfairCipher(Matrix, text_Plain, CipherText);

   printf("Matrix:\n");
   printMatrix(Matrix);

   printf("CipherText: %s\n", CipherText);

   return 0;
}
