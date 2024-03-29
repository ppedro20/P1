#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funcoesAuxiliares.h"
#include "constantes.h"
#include "funcoesAulas.h"
#include "Estruturas.h"
#include "funcoesAlunos.h"

tipoHora lerHoracLIM(char mensagem[],int minimo, int maximo)
{
    tipoHora hora;
    int controlo, falha;

    do
    {
        falha = 0;
        do
        {
            printf ("%s (hh:mm)[%d-%dh]: ", mensagem,minimo,maximo);
            controlo = scanf("%d:%d", &hora.hour, &hora.minuto);
            limpaBufferStdin();

            if (controlo != 2)
            {
                printf("\n\nERRO: deve inserir uma hora no formato indicado...\n");
            }
        }
        while (controlo != 2);

        if(hora.hour < minimo || hora.hour > maximo)
        {
            falha = 1;
            printf("\n\nERRO: Hora fora do intervalo definido\n");
        }
        if(hora.minuto < MINMIN || hora.minuto > MAXMIN)
        {
            falha = 1;
            printf("\n\nERRO: Minuto fora do intervalo definido\n");
        }
    }
    while (falha == 1);

    return hora;
}

void escreverHora (tipoHora hora)
{
    printf("%02d:%02d", hora.hour, hora.minuto);
}

tipoHora lerHora(char mensagem[])
{
    tipoHora hora;
    int controlo, falha;

    do
    {
        falha = 0;
        do
        {
            printf ("%s (hh:mm): ", mensagem);
            controlo = scanf("%d:%d", &hora.hour, &hora.minuto);
            limpaBufferStdin();

            if (controlo != 2)
            {
                printf("\n\nERRO: deve inserir uma hora no formato indicado...\n");
            }
        }
        while (controlo != 2);

        if(hora.hour < MINHORA || hora.hour > MAXHORA)
        {
            falha = 1;
            printf("\n\nERRO: Hora fora do intervalo definido\n");
        }
        if(hora.minuto < MINMIN || hora.minuto > MAXMIN)
        {
            falha = 1;
            printf("\n\nERRO: Minuto fora do intervalo definido\n");
        }
    }
    while (falha == 1);

    return hora;
}

void escreverData (tipoData data)
{
    printf("%02d-%02d-%d", data.dia, data.mes, data.ano);
}

tipoData lerData(char mensagem[])
{
    tipoData data;
    int controlo, diaMaximo, falha;

    do
    {
        falha = 0;
        do
        {
            printf ("%s (dd-mm-aaaa): ", mensagem);
            controlo = scanf("%d-%d-%d", &data.dia, &data.mes, &data.ano);
            limpaBufferStdin();

            if (controlo != 3)  // significa que o scanf n�o conseguiu atribuir valor �s 3 vari�veis (dia, mes e ano)
            {
                printf("\n\nERRO: deve inserir uma data no formato indicado...\n");
            }
        }
        while (controlo != 3);

        if (data.ano < MINANO || data.ano > MAXANO)
        {
            printf("\n\nERRO: Ano invalido [%d, %d]\n", MINANO, MAXANO);
            falha = 1;
        }
        else
        {
            switch (data.mes)
            {
            case 1:   // dias 31
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (data.dia < 1 || data.dia > 31)
                {
                    printf("\n\nERRO: Dia invalido\n\n");
                    falha = 1;
                }
                break;
            case 4:   // dias 30
            case 6:
            case 9:
            case 11:
                if (data.dia < 1 || data.dia > 30)
                {
                    printf("\n\nERRO: Dia invalido\n\n");
                    falha = 1;
                }
                break;
            case 2:    // dias 28 ou 29
                if (data.ano % 400 == 0 || (data.ano % 4 == 0 && data.ano % 100 != 0))
                {
                    diaMaximo = 29;
                }
                else
                {
                    diaMaximo = 28;
                }
                if (data.dia < 1 || data.dia > diaMaximo)
                {
                    printf("\n\nERRO: Dia invalido\n\n");
                    falha = 1;
                }
                break;
            default:
                printf("\n\nERRO: Mes invalido\n\n");
                falha = 1;
            }
        }
    }
    while (falha == 1);   // while(falha);

    return data;
}

int lerInteiro(char mensagem[], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d): ", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

int lerInteiroSlim(char mensagem[])
{
    int numero, controlo;
    do
    {
        printf("%s: ", mensagem);
        controlo = scanf ("%d", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro \n");
        }
    }
    while(controlo ==0);

    return numero;
}

float lerFloat(char mensagem[], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f): ", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores v�lidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

void lerString(char mensagem[], char vetorCaracteres[], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0'; 	//Elimina o \n da string armazenada em vetor
    }

}

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}
