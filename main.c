#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variáveis globais
int N; // Número de elementos da série
int *s_array; // Array para os N elementos da série
int x1; // Primeiro termo da série
int x2; // Segundo termo da série

// Função que será executada pelas threads
void *serie(void *arg)
{
    int n = (int)arg; // Número da thread

    // Se a thread for a primeira ou segunda, lê os 2 primeiros termos da série
    if (n == 0) {
        printf("Digite o primeiro termo da série: ");
        scanf("%d", &x1);
        s_array[0] = x1;
    }
    if (n == 1) {
        printf("Digite o segundo termo da série: ");
        scanf("%d", &x2);
        s_array[1] = x2;
    }

    // Se a thread for diferente da primeira e segunda, calcula os demais elementos
    if (n > 1) {
        s_array[n] = s_array[n-1] + s_array[n-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // Verifica se o número de argumentos é válido
    if (argc != 2) {
        printf("Erro! Número de argumentos inválido!\n");
        return 0;
    }

    // Lê o número de elementos a serem criados na série
    N = atoi(argv[1]);

    // Aloca memória para o array de elementos da série
    s_array = (int *)malloc(N * sizeof(int));

    // Cria N threads
    pthread_t threads[N];
    int i;
    for (i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, serie, (void *)i);
    }

    // Espera as N threads terminarem
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime os N elementos da série
    printf("Série gerada: ");
    for (i = 0; i < N; i++) {
        printf("%d ", s_array[i]);
    }
    printf("\n");

    return 0;
}
