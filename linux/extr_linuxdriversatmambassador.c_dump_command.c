#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  command ;

/* Variables and functions */

__attribute__((used)) static inline void dump_command (command * cmd) {
#ifdef DEBUG_AMBASSADOR
  unsigned int i;
  PRINTDB (DBG_CMD, "cmd @ %p, req: %08x, pars:",
	   cmd, /*be32_to_cpu*/ (cmd->request));
  for (i = 0; i < 3; ++i)
    PRINTDM (DBG_CMD, " %08x", /*be32_to_cpu*/ (cmd->args.par[i]));
  PRINTDE (DBG_CMD, "");
#else
  (void) cmd;
#endif
  return;
}