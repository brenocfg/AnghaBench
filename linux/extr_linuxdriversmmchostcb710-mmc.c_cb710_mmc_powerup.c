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
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_DUMP_REGS_MMC ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG0_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG1_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG2_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG3_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIGB_PORT ; 
 int /*<<< orphan*/  CB710_MMC_S2_BUSY_20 ; 
 int cb710_check_event (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_dump_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_modify_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int cb710_wait_while_busy (struct cb710_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_write_port_16 (struct cb710_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cb710_mmc_powerup(struct cb710_slot *slot)
{
#ifdef CONFIG_CB710_DEBUG
	struct cb710_chip *chip = cb710_slot_to_chip(slot);
#endif
	int err;

	/* a lot of magic for now */
	dev_dbg(cb710_slot_dev(slot), "bus powerup\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_wait_while_busy(slot, CB710_MMC_S2_BUSY_20);
	if (unlikely(err))
		return err;
	cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x80, 0);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG3_PORT, 0x80, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(1);
	dev_dbg(cb710_slot_dev(slot), "after delay 1\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_wait_while_busy(slot, CB710_MMC_S2_BUSY_20);
	if (unlikely(err))
		return err;
	cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x09, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(1);
	dev_dbg(cb710_slot_dev(slot), "after delay 2\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_wait_while_busy(slot, CB710_MMC_S2_BUSY_20);
	if (unlikely(err))
		return err;
	cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT, 0, 0x08);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	mdelay(2);
	dev_dbg(cb710_slot_dev(slot), "after delay 3\n");
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG0_PORT, 0x06, 0);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT, 0x70, 0);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG2_PORT, 0x80, 0);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG3_PORT, 0x03, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	err = cb710_wait_while_busy(slot, CB710_MMC_S2_BUSY_20);
	if (unlikely(err))
		return err;
	/* This port behaves weird: quick byte reads of 0x08,0x09 return
	 * 0xFF,0x00 after writing 0xFFFF to 0x08; it works correctly when
	 * read/written from userspace...  What am I missing here?
	 * (it doesn't depend on write-to-read delay) */
	cb710_write_port_16(slot, CB710_MMC_CONFIGB_PORT, 0xFFFF);
	cb710_modify_port_8(slot, CB710_MMC_CONFIG0_PORT, 0x06, 0);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);
	dev_dbg(cb710_slot_dev(slot), "bus powerup finished\n");

	return cb710_check_event(slot, 0);
}