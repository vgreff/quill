#include "quill/detail/HandlerCollection.h"
#include <cstdio>
#include <gtest/gtest.h>

using namespace quill;
using namespace quill::detail;

/***/
TEST(HandlerCollection, create_get)
{
  HandlerCollection hc;

  // Create a file handler
  StreamHandler* filehandler = hc.filehandler("create_get_file_handler", "w");

  // Request the same file handler
  StreamHandler* filehandler_2 = hc.filehandler("create_get_file_handler");

  // Compare the pointers
  EXPECT_EQ(filehandler, filehandler_2);
  std::remove("create_get_file_handler");
}

/***/
TEST(HandlerCollection, subscribe_get_active_same_handler)
{
  HandlerCollection hc;

  // Create a file handler
  StreamHandler* filehandler = hc.filehandler("create_get_file_handler", "w");

  // Request the same file handler
  StreamHandler* filehandler_2 = hc.filehandler("create_get_file_handler");

  // Compare the pointers
  EXPECT_EQ(filehandler, filehandler_2);

  // Check for active file handlers
  std::vector<Handler*> active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 0);

  // Subscribe the handler once
  hc.subscribe_handler(filehandler);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 1);

  // Subscribe the new handler - no effect as it is the same as before
  hc.subscribe_handler(filehandler_2);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 1);

  // Subscribe the same handler again - check no effect
  hc.subscribe_handler(filehandler);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 1);
  std::remove("create_get_file_handler");
}

/***/
TEST(HandlerCollection, subscribe_get_active_different_handlers)
{
  HandlerCollection hc;

  // Create a file handler
  StreamHandler* filehandler = hc.filehandler("create_get_file_handler_1", "w");

  // Request the same file handler
  StreamHandler* filehandler_2 = hc.filehandler("create_get_file_handler_2", "w");

  // Compare the pointers
  EXPECT_NE(filehandler, filehandler_2);

  // Check for active file handlers
  std::vector<Handler*> active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 0);

  // Subscribe the handler once
  hc.subscribe_handler(filehandler);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 1);

  // Subscribe the new handler - no effect as it is the same as before
  hc.subscribe_handler(filehandler_2);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 2);

  // Subscribe the same handler again - check no effect
  hc.subscribe_handler(filehandler);
  active_handlers = hc.active_handlers();
  EXPECT_EQ(active_handlers.size(), 2);

  std::remove("create_get_file_handler_1");
  std::remove("create_get_file_handler_2");
}