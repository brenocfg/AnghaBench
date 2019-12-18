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
typedef  int u32 ;
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_DATA_PORT ; 
 int CB710_MMC_S0_FIFO_UNDERFLOW ; 
 int /*<<< orphan*/  CB710_MMC_STATUS0_PORT ; 
 int cb710_read_port_32 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int cb710_read_port_8 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int /*<<< orphan*/  cb710_write_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void cb710_mmc_fifo_hack(struct cb710_slot *slot)
{
	/* without this, received data is prepended with 8-bytes of zeroes */
	u32 r1, r2;
	int ok = 0;

	r1 = cb710_read_port_32(slot, CB710_MMC_DATA_PORT);
	r2 = cb710_read_port_32(slot, CB710_MMC_DATA_PORT);
	if (cb710_read_port_8(slot, CB710_MMC_STATUS0_PORT)
	    & CB710_MMC_S0_FIFO_UNDERFLOW) {
		cb710_write_port_8(slot, CB710_MMC_STATUS0_PORT,
			CB710_MMC_S0_FIFO_UNDERFLOW);
		ok = 1;
	}

	dev_dbg(cb710_slot_dev(slot),
		"FIFO-read-hack: expected STATUS0 bit was %s\n",
		ok ? "set." : "NOT SET!");
	dev_dbg(cb710_slot_dev(slot),
		"FIFO-read-hack: dwords ignored: %08X %08X - %s\n",
		r1, r2, (r1|r2) ? "BAD (NOT ZERO)!" : "ok");
}