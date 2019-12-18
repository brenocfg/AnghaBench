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
struct fw_reset_cmd {void* halt_pkd; void* val; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_BOOT_CFG_A ; 
 int FW_RESET_CMD_HALT_F ; 
 int /*<<< orphan*/  INIT_CMD (struct fw_reset_cmd,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_FW_A ; 
 int /*<<< orphan*/  PCIE_FW_HALT_F ; 
 unsigned int PCIE_FW_MASTER_M ; 
 int PIORSTMODE_F ; 
 int PIORST_F ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  UPCRST_F ; 
 int /*<<< orphan*/  WRITE ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_reset_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_reset_cmd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int t4_fw_halt(struct adapter *adap, unsigned int mbox, int force)
{
	int ret = 0;

	/*
	 * If a legitimate mailbox is provided, issue a RESET command
	 * with a HALT indication.
	 */
	if (mbox <= PCIE_FW_MASTER_M) {
		struct fw_reset_cmd c;

		memset(&c, 0, sizeof(c));
		INIT_CMD(c, RESET, WRITE);
		c.val = cpu_to_be32(PIORST_F | PIORSTMODE_F);
		c.halt_pkd = cpu_to_be32(FW_RESET_CMD_HALT_F);
		ret = t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
	}

	/*
	 * Normally we won't complete the operation if the firmware RESET
	 * command fails but if our caller insists we'll go ahead and put the
	 * uP into RESET.  This can be useful if the firmware is hung or even
	 * missing ...  We'll have to take the risk of putting the uP into
	 * RESET without the cooperation of firmware in that case.
	 *
	 * We also force the firmware's HALT flag to be on in case we bypassed
	 * the firmware RESET command above or we're dealing with old firmware
	 * which doesn't have the HALT capability.  This will serve as a flag
	 * for the incoming firmware to know that it's coming out of a HALT
	 * rather than a RESET ... if it's new enough to understand that ...
	 */
	if (ret == 0 || force) {
		t4_set_reg_field(adap, CIM_BOOT_CFG_A, UPCRST_F, UPCRST_F);
		t4_set_reg_field(adap, PCIE_FW_A, PCIE_FW_HALT_F,
				 PCIE_FW_HALT_F);
	}

	/*
	 * And we always return the result of the firmware RESET command
	 * even when we force the uP into RESET ...
	 */
	return ret;
}