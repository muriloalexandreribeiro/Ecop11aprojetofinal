
#define vermelho  17
#define verde     5
#define amarelo   21

int varia = 0;
int pot = 14;

int estbut1 = 0;
int estbut2 = 0;


const int botao = 19;
const int idcorreto = 18;

int valfinal = 0;
String entrada = "";
int taxa = 0;

float taxaPorBagagem = 0.00;

// ------------------------------
// Função para medir distância
enum Estado { ESPERANDO,VerPassagem, colombia,equador, Chile, Pesagem, Final};
Estado estadoAtual = ESPERANDO;


void setup() {
  Serial.begin(115200);
  Serial.println("Sistema Iniciado - ESP32 com Máquina de Estados");
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(botao, INPUT_PULLDOWN);
  pinMode(idcorreto, INPUT_PULLDOWN);

  pinMode(pot,INPUT);

  digitalWrite(vermelho, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);
}

int pesagem(int taxaPorBagagem) {
  Serial.println("Quantas bagagens extras?");
  while (!Serial.available()) delay(100);

  int qtd = Serial.readStringUntil('\n').toInt();
  int taxaTotal = 0;

  for (int i = 0; i < qtd; i++) {
    Serial.print("Bagagem ");
    Serial.print(i + 1);
    Serial.println(": Coloque e pressione ENTER");

    while (!Serial.available()) delay(100);
    Serial.read();  // Simula ENTER

    int leituraPeso = analogRead(pot); // exemplo
    float peso = map(leituraPeso, 0, 4095, 0, 2000) / 100.0;

    Serial.print("Peso lido: ");
    Serial.print(peso);
    Serial.println(" kg");

    if (peso <= 12.8) {
      taxaTotal += taxaPorBagagem;
      Serial.println("Bagagem válida.");
    } else {
      Serial.println("Bagagem excede limite de peso.");
      i = i-1;
    }
  }

  return taxaTotal;
}

String leitura (){
  String entrada = "";
  do {
    while (!Serial.available()) {
      delay(10);
    }
    entrada = Serial.readStringUntil('\n');
    entrada.trim();
  } while (entrada.length() == 0);  // repete até digitar algo
  Serial.println("leitura: ");
  Serial.print(entrada);
  Serial.println("");
  return entrada;
}
void passagem(){
      String resposta = leitura();
        if (resposta == "colombia"){
          estadoAtual = colombia ;                           
        }
        else if (resposta == "equador"){
          estadoAtual = equador ;
        }
        else if (resposta == "chile"){
          estadoAtual = Chile ;}
        else if (resposta == "121400"){
          valfinal = 1246.00;
          taxaPorBagagem = 86.64;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;

        }
        else if (resposta == "101400"){
          valfinal = 10273.00;
          taxaPorBagagem = 86.64;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;
        }
        else if (resposta == "155400"){
          valfinal = 15223.00;
          taxaPorBagagem = 245.84;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;
        }
        else if (resposta == "624500"){
          valfinal = 6234.00;
          taxaPorBagagem = 245.84;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;
        }
        else if (resposta == "314900"){
          valfinal = 3162.00;
          taxaPorBagagem = 68.11;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;
        }
        else if (resposta == "224900"){
          valfinal = 2211.00;
          taxaPorBagagem = 68.11;
          Serial.print("Valor base: ");
          Serial.println(valfinal);
          estadoAtual = Pesagem;

        }
        }

// ------------------------------
// Loop principal
void loop() {
  int estbut1 = digitalRead(botao);
  int id = digitalRead(idcorreto);

  switch (estadoAtual) {
      case ESPERANDO:
        if(id == HIGH) {
          Serial.println("Processo iniciado");
          delay(200);
          estadoAtual= VerPassagem;
        }
        break;

      case VerPassagem:
        Serial.println("Qual sua passagem?");
        delay(1000);
        passagem();
        break;
      
      case colombia:{  
        Serial.println("qual sua classe? (premium ou economica)");
        taxaPorBagagem = 68.11;
        String resposta2;
        do {
          resposta2 = leitura();
          if (resposta2 != "premium" && resposta2 != "economica") {
            Serial.println("Opção inválida! Digite 'premium' ou 'economica'.");
          }
        } while (resposta2 != "premium" && resposta2 != "economica");

        if (resposta2 == "premium") valfinal = 3162.00;
        else if (resposta2 == "economica") valfinal = 2211.00;

        Serial.print("Valor base: ");
        Serial.println(valfinal);
        estadoAtual = Pesagem;
        break;
      }

      case equador: {
        Serial.println("qual sua classe? (premium ou economica)");
        taxaPorBagagem = 245.84;  // ex: ajuste aqui a taxa específica
        String resposta2;
        do {
          resposta2 = leitura();
          if (resposta2 != "premium" && resposta2 != "economica") {
            Serial.println("Opção inválida! Digite 'premium' ou 'economica'.");
          }
        } while (resposta2 != "premium" && resposta2 != "economica");

        if (resposta2 == "premium") valfinal = 15223.00;
        else if (resposta2 == "economica") valfinal = 6234.00;

        Serial.print("Valor base: ");
        Serial.println(valfinal);
        estadoAtual = Pesagem;
        break;
      }

      case Chile: {
        Serial.println("qual sua classe? (premium ou economica)");
        taxaPorBagagem = 86.64; // ex: ajuste aqui
        String resposta2;
        do {
          resposta2 = leitura();
          if (resposta2 != "premium" && resposta2 != "economica") {
            Serial.println("Opção inválida! Digite 'premium' ou 'economica'.");
          }
        } while (resposta2 != "premium" && resposta2 != "economica");

        if (resposta2 == "premium") valfinal = 10273.00;
        else if (resposta2 == "economica") valfinal = 1246.00;

        Serial.print("Valor base: ");
        Serial.println(valfinal);
        estadoAtual = Pesagem;
        break;
      }

      case Pesagem: {
        float taxaExtra = pesagem(taxaPorBagagem);
        valfinal += taxaExtra;
        Serial.print("Valor final: R$ ");
        Serial.println(valfinal);
        Serial.println("Esperando cliente");
        estadoAtual = ESPERANDO;
        break;
      }
  } //switch
} // loop
