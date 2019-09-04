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
typedef  int /*<<< orphan*/  loader_block ;

/* Variables and functions */

__attribute__((used)) static inline void dump_loader_block (volatile loader_block * lb) {
#ifdef DEBUG_AMBASSADOR
  unsigned int i;
  PRINTDB (DBG_LOAD, "lb @ %p; res: %d, cmd: %d, pay:",
	   lb, be32_to_cpu (lb->result), be32_to_cpu (lb->command));
  for (i = 0; i < MAX_COMMAND_DATA; ++i)
    PRINTDM (DBG_LOAD, " %08x", be32_to_cpu (lb->payload.data[i]));
  PRINTDE (DBG_LOAD, ", vld: %08x", be32_to_cpu (lb->valid));
#else
  (void) lb;
#endif
  return;
}