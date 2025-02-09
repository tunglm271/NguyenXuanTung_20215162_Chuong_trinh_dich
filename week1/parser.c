/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  } 
  else compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  } 
  else compileBlock3();
}

void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  } 
  else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecls(void) {
  // TODO
  if (lookAhead->tokenType==TK_IDENT)
    {
      compileConstDecl();
      compileConstDecls();
    }
//  else return;  OK
}

void compileConstDecl(void) {
  // TODO
  // Bạn nào code giúp với
}

void compileTypeDecls(void) {
  // TODO
}

void compileTypeDecl(void) {
  // TODO
}

void compileVarDecls(void) {
  while (lookAhead->tokenType == TK_IDENT) {
    compileVarDecl();
  }
}

void compileVarDecl(void) {
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
}

void compileSubDecls(void) {
  assert("Parsing subtoutines ....");
  while (lookAhead->tokenType == KW_PROCEDURE || lookAhead->tokenType == KW_FUNCTION) {
    if (lookAhead->tokenType == KW_PROCEDURE) {
      compileProcDecl();
    } else {
      compileFuncDecl();
    }
  }
  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
  assert("Parsing a function ....");
  eat(KW_FUNCTION);
  eat(TK_IDENT);
  compileParams();
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Function parsed ....");
}

void compileProcDecl(void) {
  assert("Parsing a procedure ....");
  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) {
  // TODO
}

void compileConstant(void) {
  // TODO
}

void compileConstant2(void) {
  // TODO
}

void compileType(void) {
   switch (lookAhead->tokenType) {
    case KW_INTEGER:
      eat(KW_INTEGER);
      break;
    case KW_CHAR:
      eat(KW_CHAR);
      break;
    case KW_STRING:
      eat(KW_STRING);
      break;
    default:
      error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

void compileBasicType(void) {
  // TODO
}

void compileParams(void) {
  if (lookAhead->tokenType == SB_LPAR) {
    eat(SB_LPAR);
    compileParam();
    while (lookAhead->tokenType == SB_SEMICOLON) {
      eat(SB_SEMICOLON);
      compileParam();
    }
    eat(SB_RPAR);
  }
}

void compileParams2(void) {
  // TODO
}

void compileParam(void) {
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
}

void compileStatements(void) {
  // TODO
}

void compileStatements2(void) {
  // TODO
}

void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileAssignSt(void) {
  assert("Parsing an assign statement ....");
  // TODO
  assert("Assign statement parsed ....");
}

void compileCallSt(void) {
  assert("Parsing a call statement ....");
  // TODO
  assert("Call statement parsed ....");
}

void compileGroupSt(void) {
  assert("Parsing a group statement ....");
  // TODO
  assert("Group statement parsed ....");
}

void compileIfSt(void) {
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE) 
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  assert("Parsing a while statement ....");
  // TODO
  assert("While statement pased ....");
}

void compileForSt(void) {
  assert("Parsing a for statement ....");
  // TODO
  assert("For statement parsed ....");
}

void compileArguments(void) {
  // TODO
}

void compileArguments2(void) {
  // TODO
}

void compileCondition(void) {
   compileExpression();
  switch (lookAhead->tokenType) {
    case SB_EQ:
      eat(SB_EQ);
      break;
    case SB_NEQ:
      eat(SB_NEQ);
      break;
    case SB_LT:
      eat(SB_LT);
      break;
    case SB_LE:
      eat(SB_LE);
      break;
    case SB_GT:
      eat(SB_GT);
      break;
    case SB_GE:
      eat(SB_GE);
      break;
    default:
      error(ERR_INVALIDCOMPARATOR, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
  compileExpression();
}

void compileCondition2(void) {
  // TODO
}

void compileExpression(void) {
  assert("Parsing an expression");
  compileTerm();
  while (lookAhead->tokenType == SB_PLUS || lookAhead->tokenType == SB_MINUS) {
    switch (lookAhead->tokenType) {
      case SB_PLUS:
        eat(SB_PLUS);
        break;
      case SB_MINUS:
        eat(SB_MINUS);
        break;
      default:
        error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
        break; 
    }
    compileTerm();
  }
  assert("Expression parsed");
}

void compileExpression2(void) {
  // TODO
}


void compileExpression3(void) {
  // TODO
}

void compileTerm(void) {
  compileFactor();
  while (lookAhead->tokenType == SB_TIMES || lookAhead->tokenType == SB_SLASH || lookAhead->tokenType == SB_MOD) {
    switch (lookAhead->tokenType) {
      case SB_TIMES:
        eat(SB_TIMES);
        break;
      case SB_SLASH:
        eat(SB_SLASH);
        break;
      case SB_MOD:
        eat(SB_MOD);
        break;
      default:
        error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
    compileFactor();
  }
}

void compileTerm2(void) {
  // TODO
}

void compileFactor(void) {
   switch (lookAhead->tokenType) {
    case TK_NUMBER:
      eat(TK_NUMBER);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      if (lookAhead->tokenType == SB_LPAR) {
        eat(SB_LPAR);
        compileExpression();
        eat(SB_RPAR);
      }
      break;
    case SB_LPAR:
      eat(SB_LPAR);
      compileExpression();
      eat(SB_RPAR);
      break;
    default:
      error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
      break;
  }
}

void compileIndexes(void) {
  // TODO
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}
