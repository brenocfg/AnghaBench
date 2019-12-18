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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_BOOT_CFG_A ; 
 int ETIMEDOUT ; 
 int FW_CMD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  PCIE_FW_A ; 
 int PCIE_FW_HALT_F ; 
 unsigned int PCIE_FW_MASTER_M ; 
 int PIORSTMODE_F ; 
 int PIORST_F ; 
 int /*<<< orphan*/  PL_RST_A ; 
 int UPCRST_F ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ t4_fw_reset (struct adapter*,unsigned int,int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int t4_fw_restart(struct adapter *adap, unsigned int mbox, int reset)
{
	if (reset) {
		/*
		 * Since we're directing the RESET instead of the firmware
		 * doing it automatically, we need to clear the PCIE_FW.HALT
		 * bit.
		 */
		t4_set_reg_field(adap, PCIE_FW_A, PCIE_FW_HALT_F, 0);

		/*
		 * If we've been given a valid mailbox, first try to get the
		 * firmware to do the RESET.  If that works, great and we can
		 * return success.  Otherwise, if we haven't been given a
		 * valid mailbox or the RESET command failed, fall back to
		 * hitting the chip with a hammer.
		 */
		if (mbox <= PCIE_FW_MASTER_M) {
			t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, 0);
			msleep(100);
			if (t4_fw_reset(adap, mbox,
					PIORST_F | PIORSTMODE_F) == 0)
				return 0;
		}

		t4_write_reg(adap, PL_RST_A, PIORST_F | PIORSTMODE_F);
		msleep(2000);
	} else {
		int ms;

		t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, 0);
		for (ms = 0; ms < FW_CMD_MAX_TIMEOUT; ) {
			if (!(t4_read_reg(adap, PCIE_FW_A) & PCIE_FW_HALT_F))
				return 0;
			msleep(100);
			ms += 100;
		}
		return -ETIMEDOUT;
	}
	return 0;
}