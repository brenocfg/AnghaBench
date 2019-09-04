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
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */

__attribute__((used)) static inline void dump_framer (hrz_dev * dev) {
#ifdef DEBUG_HORIZON
  unsigned int i;
  PRINTDB (DBG_REGS, "framer registers:");
  for (i = 0; i < 0x10; ++i)
    PRINTDM (DBG_REGS, " %02x", rd_framer (dev, i));
  PRINTDE (DBG_REGS,"");
#else
  (void) dev;
#endif
  return;
}