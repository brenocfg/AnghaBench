#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  feature_config_flags; } ;
struct bnx2x {TYPE_1__ link_params; } ;
struct TYPE_4__ {scalar_t__ aer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,...) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int BNX2X_PREV_WAIT_NEEDED ; 
 int BP_FUNC (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS ; 
 int EBUSY ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FEATURE_CONFIG_BOOT_FROM_SAN ; 
 int FW_MSG_CODE_DRV_UNLOAD_COMMON ; 
 int HW_LOCK_RESOURCE_NVRAM ; 
 int MCPR_ACCESS_LOCK_LOCK ; 
 int MCPR_NVM_SW_ARB_ARB_REQ_CLR1 ; 
 int MCP_REG_MCPR_ACCESS_LOCK ; 
 int MCP_REG_MCPR_NVM_SW_ARB ; 
 int MISC_REG_DRIVER_CONTROL_1 ; 
 int MISC_REG_DRIVER_CONTROL_7 ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  bnx2x_clean_pglue_errors (struct bnx2x*) ; 
 int bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_port_after_undi (struct bnx2x*) ; 
 TYPE_2__* bnx2x_prev_path_get_entry (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_prev_sem ; 
 int bnx2x_prev_unload_common (struct bnx2x*) ; 
 int bnx2x_prev_unload_uncommon (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_alr (struct bnx2x*) ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_prev_unload(struct bnx2x *bp)
{
	int time_counter = 10;
	u32 rc, fw, hw_lock_reg, hw_lock_val;
	BNX2X_DEV_INFO("Entering Previous Unload Flow\n");

	/* clear hw from errors which may have resulted from an interrupted
	 * dmae transaction.
	 */
	bnx2x_clean_pglue_errors(bp);

	/* Release previously held locks */
	hw_lock_reg = (BP_FUNC(bp) <= 5) ?
		      (MISC_REG_DRIVER_CONTROL_1 + BP_FUNC(bp) * 8) :
		      (MISC_REG_DRIVER_CONTROL_7 + (BP_FUNC(bp) - 6) * 8);

	hw_lock_val = REG_RD(bp, hw_lock_reg);
	if (hw_lock_val) {
		if (hw_lock_val & HW_LOCK_RESOURCE_NVRAM) {
			BNX2X_DEV_INFO("Release Previously held NVRAM lock\n");
			REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
			       (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << BP_PORT(bp)));
		}

		BNX2X_DEV_INFO("Release Previously held hw lock\n");
		REG_WR(bp, hw_lock_reg, 0xffffffff);
	} else
		BNX2X_DEV_INFO("No need to release hw/nvram locks\n");

	if (MCPR_ACCESS_LOCK_LOCK & REG_RD(bp, MCP_REG_MCPR_ACCESS_LOCK)) {
		BNX2X_DEV_INFO("Release previously held alr\n");
		bnx2x_release_alr(bp);
	}

	do {
		int aer = 0;
		/* Lock MCP using an unload request */
		fw = bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS, 0);
		if (!fw) {
			BNX2X_ERR("MCP response failure, aborting\n");
			rc = -EBUSY;
			break;
		}

		rc = down_interruptible(&bnx2x_prev_sem);
		if (rc) {
			BNX2X_ERR("Cannot check for AER; Received %d when tried to take lock\n",
				  rc);
		} else {
			/* If Path is marked by EEH, ignore unload status */
			aer = !!(bnx2x_prev_path_get_entry(bp) &&
				 bnx2x_prev_path_get_entry(bp)->aer);
			up(&bnx2x_prev_sem);
		}

		if (fw == FW_MSG_CODE_DRV_UNLOAD_COMMON || aer) {
			rc = bnx2x_prev_unload_common(bp);
			break;
		}

		/* non-common reply from MCP might require looping */
		rc = bnx2x_prev_unload_uncommon(bp);
		if (rc != BNX2X_PREV_WAIT_NEEDED)
			break;

		msleep(20);
	} while (--time_counter);

	if (!time_counter || rc) {
		BNX2X_DEV_INFO("Unloading previous driver did not occur, Possibly due to MF UNDI\n");
		rc = -EPROBE_DEFER;
	}

	/* Mark function if its port was used to boot from SAN */
	if (bnx2x_port_after_undi(bp))
		bp->link_params.feature_config_flags |=
			FEATURE_CONFIG_BOOT_FROM_SAN;

	BNX2X_DEV_INFO("Finished Previous Unload Flow [%d]\n", rc);

	return rc;
}