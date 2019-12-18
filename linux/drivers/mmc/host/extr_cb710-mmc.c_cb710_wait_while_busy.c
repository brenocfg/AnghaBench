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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_DUMP_REGS_MMC ; 
 int /*<<< orphan*/  CB710_MMC_STATUS2_PORT ; 
 int /*<<< orphan*/  CB710_MMC_STATUS_PORT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cb710_dump_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_read_port_32 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int cb710_read_port_8 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int /*<<< orphan*/  cb710_slot_to_chip (struct cb710_slot*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cb710_wait_while_busy(struct cb710_slot *slot, uint8_t mask)
{
	unsigned limit = 500000;	/* FIXME: real timeout */
	int err = 0;

#ifdef CONFIG_CB710_DEBUG
	u32 e, x;
	e = cb710_read_port_32(slot, CB710_MMC_STATUS_PORT);
#endif

	while (cb710_read_port_8(slot, CB710_MMC_STATUS2_PORT) & mask) {
		if (!--limit) {
			cb710_dump_regs(cb710_slot_to_chip(slot),
				CB710_DUMP_REGS_MMC);
			err = -ETIMEDOUT;
			break;
		}
		udelay(1);
	}

#ifdef CONFIG_CB710_DEBUG
	x = cb710_read_port_32(slot, CB710_MMC_STATUS_PORT);

	limit = 500000 - limit;
	if (limit > 100)
		dev_dbg(cb710_slot_dev(slot),
			"WAIT12: waited %d loops, mask %02X, entry val %08X, exit val %08X\n",
			limit, mask, e, x);
#endif
	return err;
}