#include "Definitions.hpp"
#include "gtest/gtest_prod.h"

#ifndef GAME_HPP
#define GAME_HPP

#define isEmpty(boardCell) (boardCell == EMPTY)

#define isPufferFish(boardCell) (boardCell == PUFFERFISH)

#define isJellyFish(boardCell) (boardCell == JELLYFISH)

#define isCrab(boardCell) (boardCell == CRAB)

#define isMoveable(boardCell) (!isEmpty(boardCell) && !isPufferFish(boardCell) && !isCrab(boardCell) && !isJellyFish(boardCell))

#define performSwap(board, y, x) {\
                                   board[y*BOARD_WIDTH + x] ^= board[y*BOARD_WIDTH + x + 1]; \
                                   board[y*BOARD_WIDTH + x + 1] ^= board[y*BOARD_WIDTH + x]; \
                                   board[y*BOARD_WIDTH + x] ^= board[y*BOARD_WIDTH + x + 1]; \
                                 }

class Game
{
public:
  Game(board_t board, int waterLevel, int searchDepth);
  move_t calculateMove();
protected:
  int countClears(board_t& board);
private:
  board_t board;
  int waterLevel;
  int searchDepth;
  bool shift(board_t& board);
  int clearCrabs(board_t& board, int waterLevel);
  int clearAll(board_t& board, int waterLevel, int previousClears);
  void performPuffer(board_t& board, int y, int x);
  void performJellyFish(board_t& board, int y, int x, int p);
  std::vector<move_t> generateMoves(board_t& board);
  board_t applyMove(board_t& board, int waterLevel, move_t& move, int previousClears);
  move_t search(board_t& board, int waterLevel, int depth, int previousClears);

  // Functions used for google tests
  FRIEND_TEST(shift, returnsFalseOnNoShifts);
  FRIEND_TEST(shift, returnsTrueOnAShift);
  FRIEND_TEST(shift, returnsTrueOnMultipleShifts);
  FRIEND_TEST(shift, performsValidShift);

  FRIEND_TEST(clearCrabs, doesNotClearCrabsUnderwater);
  FRIEND_TEST(clearCrabs, doesClearCrabsOverwater);
  FRIEND_TEST(clearCrabs, doesChainClearCrabsOverwater);

  FRIEND_TEST(clearAll, doesClear3InARow);
  FRIEND_TEST(clearAll, doesClear3InACol);
  FRIEND_TEST(clearAll, doesClear3x3);
  FRIEND_TEST(clearAll, doesClear4x4);

  FRIEND_TEST(performPuffer, doesPerformValidPuffer);

  FRIEND_TEST(performJellyFish, doesPerformValidJellyFish);
};

#endif
