#include <stdio.h>
#include <stdint.h>

void print_rm_table_1(uint8_t rm) {
  switch(rm) {
    case 0:
      printf("[BX+SI]");
      break;
    case 1:
      printf("[BX+DI]");
      break;
    case 2:
      printf("[BP+SI]");
      break;
    case 3:
      printf("[BP+DI]");
      break;
    case 4:
      printf("[SI]");
      break;
    case 5:
      printf("[DI]");
      break;
    case 6:
      printf("[ILLEGAL!]");
      break;
    case 7:
      printf("[BX]");
      break;
  }
}

void print_rm_table_2(uint8_t rm, uint16_t offset) {
  switch(rm) {
    case 0:
      printf("[BX+SI+%d]", offset);
      break;
    case 1:
      printf("[BX+DI+%d]", offset);
      break;
    case 2:
      printf("[BP+SI+%d]", offset);
      break;
    case 3:
      printf("[BP+DI+%d]", offset);
      break;
    case 4:
      printf("[SI+%d]", offset);
      break;
    case 5:
      printf("[DI+%d]", offset);
      break;
    case 6:
      printf("[BP+%d]", offset);
      break;
    case 7:
      printf("[BX+%d]", offset);
      break;
  }
}

void print_byte_reg(uint8_t reg) {
  switch(reg) {
    case 0:
      printf("AL");
      break;
    case 1:
      printf("CL");
      break;
    case 2:
      printf("DL");
      break;
    case 3:
      printf("BL");
      break;
    case 4:
      printf("AH");
      break;
    case 5:
      printf("CH");
      break;
    case 6:
      printf("DH");
      break;
    case 7:
      printf("BH");
      break;
  }
}


void print_word_reg(uint8_t reg) {
  switch(reg) {
    case 0:
      printf("AX");
      break;
    case 1:
      printf("CX");
      break;
    case 2:
      printf("DX");
      break;
    case 3:
      printf("BX");
      break;
    case 4:
      printf("SP");
      break;
    case 5:
      printf("BP");
      break;
    case 6:
      printf("SI");
      break;
    case 7:
      printf("DI");
      break;
  }
}

void print_args(uint8_t *instruction) {
  uint8_t mod = instruction[1] >> 6;
  uint8_t reg = (instruction[1] >> 3) & 0x7;
  uint8_t rm = instruction[1] & 0x7;

  if (mod == 0) {
    print_rm_table_1(rm);
    printf(", ");
    print_byte_reg(reg);
    printf("\n");
  } else if (mod == 1) {
    print_rm_table_2(rm, instruction[2]);
    printf(", ");
    print_byte_reg(reg);
    printf("\n");
  } else if (mod == 2) {
    uint16_t offset = ((uint16_t) instruction[3] << 8) + instruction[2];
    print_rm_table_2(rm, offset);
    printf(", ");
    print_byte_reg(reg);
    printf("\n");
  } else {
    print_byte_reg(rm);
    printf(", ");
    print_byte_reg(reg);
    printf("\n");
  }
}


void print_opcode(uint8_t *instruction) {
  switch(instruction[0]) {
    case 0x00:
      printf("ADD ");
      print_args(instruction);
      break;
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
      puts("ADD");
      break;
    case 0x06:
      puts("PUSH ES");
      break;
    case 0x07:
      puts("POP ES");
      break;
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:
    case 0x0C:
    case 0x0D:
      puts("OR");
      break;
    case 0x0E:
      puts("PUSH");
      break;
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
      puts("ADDC");
      break;
    case 0x16:
      puts("PUSH SS");
      break;
    case 0x17:
      puts("POP SS");
      break;
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
      puts("SBB");
      break;
    case 0x1E:
      puts("PUSH DS");
      break;
    case 0x1F:
      puts("POP DS");
      break;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      puts("AND");
      break;
    case 0x26:
      puts("ES:");
      break;
    case 0x27:
      puts("DAA");
      break;
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
      puts("SUB");
      break;
    case 0x2E:
      puts("CS:");
      break;
    case 0x2F:
      puts("DAS");
      break;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
      puts("XOR");
      break;
    case 0x36:
      puts("SS:");
      break;
    case 0x37:
      puts("AAA");
      break;
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
      puts("CMP");
      break;
    case 0x3E:
      puts("DS:");
      break;
    case 0x3F:
      puts("AAS");
      break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
      puts("INC");
      break;
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
      puts("DEC");
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
      puts("PUSH");
      break;
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
      puts("POP");
      break;
    case 0x70:
      puts("JO");
      break;
    case 0x71:
      puts("JNO");
      break;
    case 0x72:
      puts("JB");
      break;
    case 0x73:
      puts("JNB");
      break;
    case 0x74:
      puts("JZ");
      break;
    case 0x75:
      puts("JNZ");
      break;
    case 0x76:
      puts("JBE");
      break;
    case 0x77:
      puts("JA");
      break;
    case 0x78:
      puts("JS");
      break;
    case 0x79:
      puts("JNS");
      break;
    case 0x7A:
      puts("JPE");
      break;
    case 0x7B:
      puts("JPO");
      break;
    case 0x7C:
      puts("JL");
      break;
    case 0x7D:
      puts("JGE");
      break;
    case 0x7E:
      puts("JLE");
      break;
    case 0x7F:
      puts("JG");
      break;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
      puts("GRP1 EXTENSION");
      break;
    case 0x84:
    case 0x85:
      puts("TEST");
      break;
    case 0x86:
    case 0x87:
      puts("XCHG");
      break;
    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:
    case 0x8C:
      puts("MOV");
      break;
    case 0x8D:
      puts("LEA");
      break;
    case 0x8E:
      puts("MOV");
      break;
    case 0x8F:
      puts("POP");
      break;
    case 0x90:
      puts("NOP");
      break;
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
      puts("XCHG");
      break;
    case 0x98:
      puts("CBW");
      break;
    case 0x99:
      puts("CWD");
      break;
    case 0x9A:
      puts("CALL");
      break;
    case 0x9B:
      puts("WAIT");
      break;
    case 0x9C:
      puts("PUSHF");
      break;
    case 0x9D:
      puts("POPF");
      break;
    case 0x9E:
      puts("SAHF");
      break;
    case 0x9F:
      puts("LAHF");
      break;
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
      puts("MOV");
      break;
    case 0xA4:
      puts("MOVSB");
      break;
    case 0xA5:
      puts("MOVSW");
      break;
    case 0xA6:
      puts("CMPSB");
      break;
    case 0xA7:
      puts("CMPSW");
      break;
    case 0xA8:
    case 0xA9:
      puts("TEST");
      break;
    case 0xAA:
      puts("STOSB");
      break;
    case 0xAB:
      puts("STOSW");
      break;
    case 0xAC:
      puts("LODSB");
      break;
    case 0xAD:
      puts("LODSW");
      break;
    case 0xAE:
      puts("SCASB");
      break;
    case 0xAF:
      puts("SCASW");
      break;
    case 0xB0:
    case 0xB1:
    case 0xB2:
    case 0xB3:
    case 0xB4:
    case 0xB5:
    case 0xB6:
    case 0xB7:
    case 0xB8:
    case 0xB9:
    case 0xBA:
    case 0xBB:
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:
      puts("MOV");
      break;
    case 0xC2:
    case 0xC3:
      puts("RET");
      break;
    case 0xC4:
      puts("LES");
      break;
    case 0xC5:
      puts("LDS");
      break;
    case 0xC6:
    case 0xC7:
      puts("MOV");
      break;
    case 0xCA:
    case 0xCB:
      puts("RETF");
      break;
    case 0xCC:
    case 0xCD:
      puts("INT");
      break;
    case 0xCE:
      puts("INTO");
      break;
    case 0xCF:
      puts("IRET");
    case 0xD0:
    case 0xD1:
    case 0xD2:
    case 0xD3:
      puts("GRP2 EXTENSION");
      break;
    case 0xD4:
      puts("AAM");
      break;
    case 0xD5:
      puts("AAD");
      break;
    case 0xD7:
      puts("XLAT");
      break;
    case 0xE0:
      puts("LOOPNZ");
      break;
    case 0xE1:
      puts("LOOPZ");
      break;
    case 0xE2:
      puts("LOOP");
      break;
    case 0xE3:
      puts("JCXZ");
      break;
    case 0xE4:
    case 0xE5:
      puts("IN");
      break;
    case 0xE6:
    case 0xE7:
      puts("OUT");
      break;
    case 0xE8:
      puts("CALL");
      break;
    case 0xE9:
    case 0xEA:
    case 0xEB:
      puts("JMP");
      break;
    case 0xEC:
    case 0xED:
      puts("IN");
      break;
    case 0xEE:
    case 0xEF:
      puts("OUT");
      break;
    case 0xF0:
      puts("LOCK");
      break;
    case 0xF2:
      puts("REPNZ");
      break;
    case 0xF3:
      puts("REPZ");
      break;
    case 0xF4:
      puts("HLT");
      break;
    case 0xF5:
      puts("CMC");
      break;
    case 0xF6:
      puts("GROUP 3a EXTENSION");
      break;
    case 0xF7:
      puts("GROUP 3b EXTENSION");
      break;
    case 0xF8:
      puts("CLC");
      break;
    case 0xF9:
      puts("STC");
      break;
    case 0xFA:
      puts("CLI");
      break;
    case 0xFB:
      puts("STI");
      break;
    case 0xFC:
      puts("CLD");
      break;
    case 0xFD:
      puts("STD");
      break;
    case 0xFE:
    case 0xFF:
      puts("GROUP 4 EXTENSION");
      break;
    default:
      puts("INVALID OPCODE");
  }
}

int main(int argc, char const *argv[]) {
  printf("Enter Opcode :\n");
  uint8_t opcode[100] = {0};
  int i = 0;
  while((scanf("%x",&opcode[i])) != EOF) {
      i++;
  }
  print_opcode(opcode);
  return 0;
}
