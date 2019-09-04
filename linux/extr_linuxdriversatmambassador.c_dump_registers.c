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
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */

__attribute__((used)) static inline void dump_registers (const amb_dev * dev) {
#ifdef DEBUG_AMBASSADOR
  if (debug & DBG_REGS) {
    size_t i;
    PRINTD (DBG_REGS, "reading PLX control: ");
    for (i = 0x00; i < 0x30; i += sizeof(u32))
      rd_mem (dev, i);
    PRINTD (DBG_REGS, "reading mailboxes: ");
    for (i = 0x40; i < 0x60; i += sizeof(u32))
      rd_mem (dev, i);
    PRINTD (DBG_REGS, "reading doorb irqev irqen reset:");
    for (i = 0x60; i < 0x70; i += sizeof(u32))
      rd_mem (dev, i);
  }
#else
  (void) dev;
#endif
  return;
}