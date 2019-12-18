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
typedef  int u8 ;
typedef  int u16 ;
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int CB710_MMC_S0_FIFO_UNDERFLOW ; 
 int CB710_MMC_S1_RESET ; 
 int /*<<< orphan*/  CB710_MMC_STATUS0_PORT ; 
 int /*<<< orphan*/  CB710_MMC_STATUS1_PORT ; 
 int CB710_MMC_STATUS_ERROR_EVENTS ; 
 int /*<<< orphan*/  CB710_MMC_STATUS_PORT ; 
 int EIO ; 
 int cb710_read_port_16 (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int /*<<< orphan*/  cb710_write_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cb710_check_event(struct cb710_slot *slot, u8 what)
{
	u16 status;

	status = cb710_read_port_16(slot, CB710_MMC_STATUS_PORT);

	if (status & CB710_MMC_S0_FIFO_UNDERFLOW) {
		/* it is just a guess, so log it */
		dev_dbg(cb710_slot_dev(slot),
			"CHECK : ignoring bit 6 in status %04X\n", status);
		cb710_write_port_8(slot, CB710_MMC_STATUS0_PORT,
			CB710_MMC_S0_FIFO_UNDERFLOW);
		status &= ~CB710_MMC_S0_FIFO_UNDERFLOW;
	}

	if (status & CB710_MMC_STATUS_ERROR_EVENTS) {
		dev_dbg(cb710_slot_dev(slot),
			"CHECK : returning EIO on status %04X\n", status);
		cb710_write_port_8(slot, CB710_MMC_STATUS0_PORT, status & 0xFF);
		cb710_write_port_8(slot, CB710_MMC_STATUS1_PORT,
			CB710_MMC_S1_RESET);
		return -EIO;
	}

	/* 'what' is a bit in MMC_STATUS1 */
	if ((status >> 8) & what) {
		cb710_write_port_8(slot, CB710_MMC_STATUS1_PORT, what);
		return 1;
	}

	return 0;
}