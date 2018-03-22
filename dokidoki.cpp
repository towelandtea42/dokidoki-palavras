#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;


typedef struct {
	char pal[20];
	int meninas[3]; //ordem: sayori, natsuki, yuri
}palavra;

//----------EXPLICAÇÃO IMPORTANTE----------

//Cada palavra pode ter um dos seguintes valores pra cada uma:
// - 1 (Meh)
// - 2 (Gosta)
// - 3 (Gosta muito)
//Isso é utilizado na consulta.

//-----FIM DA EXPLICAÇÃO IMPORTANTE-----

//vetor com a lista completa de palavras, sempre ordenadas
vector <palavra> todas_as_palavras;


//----------FUNÇÕES UTILIZADAS----------

	//Lê as palavras do arquivo
	void ler_palavras(FILE* in);
	//Busca binária em todas_as_palavras
	int bb (char x[], int ini, int fim);
	//Função auxiliar para imprimir consulta
	void imprime_consulta(palavra p, int i);
	//Função para consultar a palavra
	void consultar_palavra();
	//Função para exibir menu (o rly)
	void exibe_menu(int menu);
	//Função que exibe tutorial do good ending
	int tutorial_good_ending(int menu);
	//Função que gerencia o tutorial do good ending
	void good_ending();
	//Função para listar palavras de uma das 3
	void lista_palavras(int quem);

//----------FUNÇÕES NÃO UTILIZADAS----------

	/*Essas funções não estão sendo usadas, mas usei pra mexer 
	inicialmente no arquivo que tinha a lista de palavras. Resumindo:
	estão aí pra se vc quiser mexer em algo.*/
	bool ordena (palavra i,palavra j);
	void imprimir_palavras_bonitinho(FILE* out);
	void imprime (FILE* out, palavra aux);
	void imprimir_palavras_feio(FILE* out);


//###########--------------------###########

//-------------O MAIN() TÁ AQUI-------------

int main () {
	FILE * palavrasdoki = fopen("palavrasdoki.txt","r");
	
	//Variáveis auxiliares
	int deseja_fazer = 0; //Opção desejada
	string str_aux; //Idiot proofing code
	bool digitou_opcao_existente = 1; //Evita exibir menu 2 vezes
	
	//Carrega palavras do arquivo
	ler_palavras(palavrasdoki);
	
	//Mais texto de menu
	exibe_menu(1);
	
	while(deseja_fazer!=3) { //O 3 é sair do programa
		
		//Exibe o menu e lê a opção desejada
		if(digitou_opcao_existente) exibe_menu(2);
		scanf("%d", &deseja_fazer);
		getline(cin,str_aux);
		
		//Checa opção escolhida
		//Os ifs são pra garantir que só digitou o número
		switch(deseja_fazer) {
			
			/*Pensei em fazer uma função que calcula a felicidade de 
			cada uma a partir das escolhas, de forma que ainda dê pra
			fazer consulta e digitar alguma coisa informando se
			escolheu a palavra consultada. Daí dá pra exibir a soma
			parcial a cada escolha. Preguiça kkkkk*/
			
			case 1: //Consulta palavras até não querer mais
					if(str_aux[0]=='\0'||str_aux[0]=='\n') {
						consultar_palavra();
						digitou_opcao_existente = 1;
						break;
					}
			case 2: //Explicação de como obter o Good Ending
					if(str_aux[0]=='\0'||str_aux[0]=='\n') {
						good_ending();
						digitou_opcao_existente = 1;
						break;
					}
			case 3: //Termina o programa
					if(str_aux[0]=='\0'||str_aux[0]=='\n') break;
			default: printf("\n ~ Acao nao existe!\n");
					printf("\n -----------------------------------------------------\n");
					printf("\n Pare de encher o saco e digite um numero valido dessa");
					printf("\nvez: ");
					digitou_opcao_existente = 0;
		}
		
	}
	
	fclose (palavrasdoki);
	
	return 0;
}

//###########--------------------###########

//------------FUNÇÕES UTILIZADAS-------------

//Lê as palavras do arquivo
void ler_palavras(FILE* in) {
	
	//Variável auxiliar
	palavra palavra_aux;

	while(fscanf(in,"%s", palavra_aux.pal)&&strcmp(palavra_aux.pal,"#")) {
		//Lê as palavras do arquivo e insere no vetor
		fgetc(in);
		fscanf(in,"%d %d %d", &palavra_aux.meninas[0], &palavra_aux.meninas[1], &palavra_aux.meninas[2]);
		fgetc(in);
		
		todas_as_palavras.push_back(palavra_aux);
	}
	
	//sort(todas_as_palavras.begin(),todas_as_palavras.end(), ordena);
}


//Busca binária em todas_as_palavras
int bb (char x[], int ini, int fim) {
	
	int i = (ini+fim)/2;
	int comp = strcmp(todas_as_palavras[i].pal,x);
	
	if(ini==i&&comp!=0) return -1;
	if(comp==0) return i;
	else if(comp<0) return bb (x, i+1, fim);
	else return bb (x, ini, i);
	
}


//Função auxiliar para imprimir consulta
//Tava me complicando pra imprimir na ordem, então isso pode ser
//considerado um armengue kkkkk
void imprime_consulta(palavra p, int i) {
	
	//Variáveis auxiliares
	int sayori = p.meninas[0];
	int natsuki = p.meninas[1];
	int yuri = p.meninas[2];
	bool aux_igual=0;
	/*Esse aux_igual é pq vi que algumas palavras da Yuri têm
	valor 1 pra Natsuki e pra Sayori, daí fiz isso pra não deixar
	passar palavras repetidas. Desde a maratona do ano passado que
	eu não implemento nada, então dê um desconto pq pelo menos tá
	bem explicado kkkkk */
	
	//A partir daqui imprime organizadinho os nomes correspondentes
	if(sayori==i)  {
		printf("Sayori");
		aux_igual=1;
	}
	
	if(natsuki==i)  {
		if(aux_igual) printf(", ");
		printf("Natsuki");
		aux_igual=1;
	}
	
	if(yuri==i)  {
		if(aux_igual) printf(", ");
		printf("Yuri");
		aux_igual=1;
	}
	
}

//Função para listar palavras de uma das 3
void lista_palavras(int quem) {
	//Variável auxiliar
	int cont_aux = 0;
	int tam_ult_palavra=0;
	
	switch(quem){
		case 0: printf("\n  ~ Lista de palavras da Sayori:\n");
				break;
		case 1: printf("\n  ~ Lista de palavras da Natsuki:\n");
				break;
		case 2: printf("\n  ~ Lista de palavras da Yuri:\n");
				break;
		default: break;
	}
	for(int i=0; i<(int)todas_as_palavras.size();i++) {
		if(todas_as_palavras[i].meninas[quem]==3) {
			if(cont_aux%3==0)printf("\n    ");
			else printf("%*c", (15-tam_ult_palavra), ' ');
			printf("+ %s", todas_as_palavras[i].pal);
			tam_ult_palavra = strlen(todas_as_palavras[i].pal);
			cont_aux++;
		}
	}
	printf("\n");
}


//Função para consultar a palavra
void consultar_palavra(){
	
	//Aqui é só pra ficar organizado, mas não faz nada dms
	printf("\n########--------------------------------------########\n");
	printf("\n  - CONSULTAS -\n");
	printf("\n  ~ Caso deseje sair, digite \"sair\", sem as aspas.");
	printf("\n  ~ Sempre digite as palavras em letras minusculas.");
	printf("\n  ~ Digite apenas uma palavra por vez.");
	printf("\n  ~ Digite  \"sayori\", \"natsuki\" ou \"yuri\" (sem as as-");
	printf("\n pas) para consultar a lista completa de uma das tres.");
	printf("\n  ----------------------------------------------------\n");
	
	//Variáveis auxiliares
	char palavra_lida[20];
	int aux_res; //guarda resultado da busca binária
	bool consulta_valida = true; /*Acrescentada unicamente para 
									possibilitar a zoeira*/
	
	while(true) { //sai do loop quando digita "sair"
		
		//Dava pra deixar só o primeiro, então fique à vontade pra tirar
		if(consulta_valida) printf("\n  Digite palavra a ser consultada: ");
		else {
			printf("\n  Digite palavra a ser consultada (dessa vez uma vali-");
			printf("\n da, por favor): ");
		}
		
		/*Lê a palavra, confere se não foi "sair"  ou se não pediu pra
		listar as palavras de uma das 3 e dps faz busca binária*/
		scanf("%s", palavra_lida);
		if(strcmp(palavra_lida, "sair")==0) break;
		
		if(strcmp(palavra_lida, "sayori")==0) {
			lista_palavras(0);
			printf("\n  ----------------------------------------------------\n");
			consulta_valida=1;
			continue;
		}
		else if(strcmp(palavra_lida, "natsuki")==0) {
			lista_palavras(1);
			printf("\n  ----------------------------------------------------\n");
			consulta_valida=1;
			continue;
		}
		else if(strcmp(palavra_lida, "yuri")==0) {
			lista_palavras(2);
			printf("\n  ----------------------------------------------------\n");
			consulta_valida=1;
			continue;
		}
		aux_res = bb(palavra_lida, 0, todas_as_palavras.size());
		
		//Idiot proofing code/zoeira
		if(aux_res==-1) {
			printf("\n  ~ Palavra invalida!");
			printf("\n  ~ Eh por causa de pessoas como vc que eu tenho que ");
			printf("\n fazer codigos a prova de idiotas...\n");
			printf("  ~ Espero que esteja feliz.\n");
			printf("\n  ----------------------------------------------------\n");
			consulta_valida = 0;
		}
		
		//Aqui imprime a consulta bonitinho
		else {
			consulta_valida = 1;
			for(int i=3;i>0;i--) {
		
				printf("    - ");
				switch(i) {
					case 3: printf("Gosta muito: ");
							break;
					case 2: printf("Gosta: ");
							break;
					case 1: printf("Meh: ");
							break;
					default: break;
				}
				imprime_consulta(todas_as_palavras[aux_res], i);
				printf("\n");
				
			}
			
			printf("\n  ----------------------------------------------------\n");
			
		}
		
	}
	
	printf("\n                 - FIM DAS CONSULTAS -\n");
	printf("\n########--------------------------------------########\n");
	
}


//Função para exibir menus em geral (o rly)
void exibe_menu(int menu) {
	
	switch(menu) {
		
		case 1: //Abertura do programa
				printf("\n~ Ola, bem vindo!");
				printf("\n~ Eu deveria estar estudando, mas parei pra fazer esse");
				printf("\ncodigo. Espero que pelo menos seja util pra vc kkk");
				printf("\n~ Boa sorte pra conseguir o Good Ending de DDLC! :D\n");
				break;
				
		case 2: //Menu principal
				printf("\n - MENU PRINCIPAL -\n");
				printf("\n Opcoes:\n");
				printf("\n  1 - Consultar palavra");
				printf("\n  2 - Passo a passo de como obter o Good Ending");
				printf("\n  3 - Sair do programa\n");
				printf("\n -----------------------------------------------------\n");
				printf("\n Digite o numero correspondente ao que deseja fazer: ");
				break;
			
		case 3: //Menu do Good Ending
				printf("\n  ~ Eh fundamental que vc leia o item 2, o nome nao eh ");
				printf("\n \"Aspectos importantes\" a toa.\n");
				printf("\n  Opcoes:\n");
				printf("\n    1 - Recomendacoes iniciais");
				printf("\n    2 - Aspectos importantes (contem spoilers)");
				printf("\n    3 - Ato 1");
				printf("\n    4 - Ato 2");
				printf("\n    5 - Terminando o jogo (perdi)");
				printf("\n    6 - Voltar ao menu principal\n");
				printf("\n  ----------------------------------------------------\n");
				printf("\n  Digite numero correspondente a opcao: ");
				break;
				
		default: break;
	}
}


//Função que exibe tutorial do good ending
int tutorial_good_ending(int menu) {
	switch(menu){
		case 1: //Recomendacoes iniciais
			printf("\n  Recomendacoes iniciais:\n");
			printf("\n    1 - Se ainda nao resetou o jogo, va para a pasta ");
			printf("\n  \"Game\" e delete o arquivo \"firstrun\". Isto ira rese-");
			printf("\n  tar seu jogo.");
			printf("\n    2 - Nas configuracoes do jogo, marque  \"Unseen");
			printf("\n  Text\" e \"After Choice\" para pular as cenas mais ra-");
			printf("\n  pido.");
			printf("\n    3 - Use a tecla \"Ctrl\" para pular as cenas ja vis-");
			printf("\n  tas.");
			printf("\n    4 - Nao faca isso se for sua primeira vez jogando");
			printf("\n  DDLC. Vale mais a pena se vc ja estiver apegado com");
			printf("\n  as personagens.\n");
			printf("\n  Aperte \"Enter\" para continuar...");
			return 0;
		case 2: //Aspectos importantes
			printf("\n  Aspectos importantes:\n");
			printf("\n    1 - Para conseguir o GE, eh preciso obter todas");
			printf("\n  as tres cenas especiais de cada personagem. Ou seja,");
			printf("\n  vc deve fazer as tres rotas (Sayori, Natsuki, Yuri)");
			printf("\n  no Ato 1.");
			printf("\n    2 - A ordem das rotas nao importa.");
			printf("\n    3 - Salve ao chegar no primeiro poema, eh preciso");
			printf("\n  voltar para ele sempre que concluir uma das rotas.");
			printf("\n    4 - Salve sempre que concluir uma das rotas. O ");
			printf("\n  saving deve ser feito ANTES DA MORTE DA SAYORI.");
			printf("\n    5 - Apos a concluir a ultima rota nao precisa sal-");
			printf("\n  var, so continue o jogo ate o Ato 2.\n");
			printf("\n  Aperte \"Enter\" para continuar...");
			return 0;
		case 3: //Ato 1
			printf("\n  Ato 1:\n");
			printf("\n    Vou assumir que vc leu o item 2. Se nao tiver li-");
			printf("\n  do, VA LER. Alem disso, se eu nao mencionar alguma ");
			printf("\n  escolha aqui, eh pq nao influencia.\n");
			printf("\n    ~ Rota da Sayori:");
			printf("\n    1 - Dedique todos os poemas a ela.");
			printf("\n    2 - Confesse seu amor por ela.");
			printf("\n    3 - Salve assim que a cena de confessar acabar.\n");
			printf("\n    ~ Rota da Natsuki:");
			printf("\n    1 - Dedique todos os poemas a ela.");
			printf("\n    2 - Escolha ajuda-la nas arrumacoes pro festival.");
			printf("\n    3 - Salve assim que ela for embora da sua casa.\n");
			printf("\n    ~ Rota da Yuri:");
			printf("\n    1 - Dedique todos os poemas a ela.");
			printf("\n    2 - Escolha ajuda-la nas arrumacoes pro festival.");
			printf("\n    3 - Salve assim que ela for embora da sua casa.\n");
			printf("\n  Aperte \"Enter\" para continuar...");
			return 0;
		case 4: //Ato 2
			printf("\n  Ato 2:\n");
			printf("\n    1 - Se ja conhece as duas rotas, pegue a da Yuri,");
			printf("\n  eh mais curta.");
			printf("\n    2 - Se nao jogou a rota da Natsuki ainda, JOGUE, ");
			printf("\n  EH TOP.");
			printf("\n    3 - Suas escolhas aqui nao importam, so chegue em");
			printf("\n  Just Monika como achar melhor.\n");
			printf("\n  Aperte \"Enter\" para continuar...");
			return 0;
		case 5: //Terminando o jogo
			printf("\n  Terminando o jogo:\n");
			printf("\n    1 - Nao tenho certeza, mas li que precisa passar ");
			printf("\n  uns minutos com a Monika antes de deleta-la (por ");
			printf("\n  causa da cena dela). Deletei apos escrever o poema ");
			printf("\n  bugado.");
			printf("\n    2 - Delete a Monika.");
			printf("\n    3 - Pega um lencinho e aproveita o final.\n");
			printf("\n  Aperte \"Enter\" para continuar...");
			return 0;
		default: return 6;
	}
	
}
		
//Função que gerencia o tutorial do good ending
void good_ending() {
	
	//Variáveis auxiliares
	int deseja_fazer = 0; //Opção desejada
	string str_aux; //Idiot proofing code
	bool digitou_opcao_existente = 1; //Evita exibir menu 2 vezes
	
	
	printf("\n########--------------------------------------########\n");
	printf("\n  - TUTORIAL GOOD ENDING -\n");
	printf("\n  ~ PARABENS! Se vc chegou aqui eh pq tbm nao faz a ");
	printf("\n menor ideia do que fazer para obter o Good Ending. O");
	printf("\n tutorial esta separado em topicos, para facilitar sua");
	printf("\n vida.\n");
	
	while(deseja_fazer!=6) { //O 6 é voltar ao menu principal
		
		//Exibe o menu e lê a opção desejada
		if(digitou_opcao_existente) exibe_menu(3);
		scanf("%d", &deseja_fazer);
		getline(cin,str_aux);
		
		//Checa opção escolhida
		//Os ifs são pra garantir que só digitou o número
		if(deseja_fazer<1||deseja_fazer>6) str_aux = "tente de novo";
		else if(deseja_fazer == 6) break;
		
		
		if(str_aux[0]=='\0'||str_aux[0]=='\n') {
			deseja_fazer = tutorial_good_ending(deseja_fazer);
			digitou_opcao_existente = 1;
			do {
				getline(cin,str_aux);
			} while(str_aux[0]=='\n');
			printf("\n  ----------------------------------------------------\n");
			printf("\n  - TUTORIAL GOOD ENDING -\n");
		}
		else {
			printf("\n  ~ Este item nao existe!\n");
			printf("\n  ----------------------------------------------------\n");
			printf("\n  Pare de encher o saco e digite um numero valido des-");
			printf("\n sa vez: ");
			digitou_opcao_existente = 0;
		}
		
	}
	
	printf("\n                 - FIM DO TUTORIAL -\n");
	printf("\n########--------------------------------------########\n");
	
}
		

//###########--------------------###########

//----------FUNÇÕES NÃO UTILIZADAS----------

//Função passada de parâmetro pra sort()
//E o sort() não está sendo mais utilizado kkkkk
bool ordena (palavra i,palavra j) { 
	if (strcmp(i.pal,j.pal)<=0) return true; 
	else return false;
}


//Essa é só pra ajudar na de imprimir bonitinho
void imprime (FILE* out, palavra aux){
	
	fprintf(out, "- %s: ", aux.pal);
	fprintf(out, "%d, ", aux.meninas[0]);
	fprintf(out, "%d, ", aux.meninas[1]);
	fprintf(out, "%d\n", aux.meninas[2]);
	
}

//Função que imprime arquivo com a lista de palavras separada por personagem
void imprimir_palavras_bonitinho(FILE* out) {
	
	//Variáveis auxiliares
	int aux_tamanho_vetor = (int)todas_as_palavras.size();
	vector <bool> marcado;
	
	/*Passa 3 vezes pelo vetor*/
	
	fprintf(out, "Sayori:\n\n");
	
	for(int i=0;i<aux_tamanho_vetor;i++) {
		
		if(todas_as_palavras[i].meninas[0]==3) {
			imprime(out, todas_as_palavras[i]);
			marcado.push_back(true);
		}
		
		else marcado.push_back(false);
	}
	
	
	fprintf(out, "\n########------------########\n");
	fprintf(out, "\nNatsuki:\n\n");
	
	for(int i=0;i<aux_tamanho_vetor;i++) {
		
		if(marcado[i]) continue;
		
		else if(todas_as_palavras[i].meninas[1]==3) {
			imprime(out, todas_as_palavras[i]);
			marcado[i] = true;
		}
	}
	
	
	fprintf(out, "\n########------------########\n");
	fprintf(out, "\nYuri:\n\n");
	
	for(int i=0;i<aux_tamanho_vetor;i++) {
		
		if(marcado[i]) continue;
		
		else if(todas_as_palavras[i].meninas[2]==3)
			imprime(out, todas_as_palavras[i]);
	}
	
}

//Imprime palavras em ordem alfabética, sem separação
void imprimir_palavras_feio(FILE* out) {
	
	for(int i=0;i<(int)todas_as_palavras.size();i++) {
		fprintf(out, "%s ", todas_as_palavras[i].pal);
		fprintf(out, "%d ",  todas_as_palavras[i].meninas[0]);
		fprintf(out, "%d ",  todas_as_palavras[i].meninas[1]);
		fprintf(out, "%d\n",  todas_as_palavras[i].meninas[2]);
	}
	fprintf(out, "#");
		
}
