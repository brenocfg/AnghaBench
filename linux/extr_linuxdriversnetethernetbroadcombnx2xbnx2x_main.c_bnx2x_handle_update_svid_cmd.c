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
struct bnx2x_func_switch_update_params {int vlan; int /*<<< orphan*/  changes; } ;
struct TYPE_3__ {struct bnx2x_func_switch_update_params switch_update; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; TYPE_1__ params; } ;
struct bnx2x {int mf_ov; int /*<<< orphan*/  func_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  e1hov_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_SWITCH_UPDATE ; 
 int /*<<< orphan*/  BNX2X_F_UPDATE_SD_VLAN_TAG_CHNG ; 
 int /*<<< orphan*/  BNX2X_MSG_MCP ; 
 int BP_ABS_FUNC (struct bnx2x*) ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OEM_UPDATE_SVID_FAILURE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OEM_UPDATE_SVID_OK ; 
 int FUNC_MF_CFG_E1HOV_TAG_DEFAULT ; 
 int FUNC_MF_CFG_E1HOV_TAG_MASK ; 
 scalar_t__ IS_MF_BD (struct bnx2x*) ; 
 scalar_t__ IS_MF_UFP (struct bnx2x*) ; 
 int MF_CFG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ NIG_REG_LLH0_FUNC_VLAN_ID ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* func_mf_config ; 
 int /*<<< orphan*/  memset (struct bnx2x_func_state_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_handle_update_svid_cmd(struct bnx2x *bp)
{
	struct bnx2x_func_switch_update_params *switch_update_params;
	struct bnx2x_func_state_params func_params;

	memset(&func_params, 0, sizeof(struct bnx2x_func_state_params));
	switch_update_params = &func_params.params.switch_update;
	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SWITCH_UPDATE;

	/* Prepare parameters for function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	if (IS_MF_UFP(bp) || IS_MF_BD(bp)) {
		int func = BP_ABS_FUNC(bp);
		u32 val;

		/* Re-learn the S-tag from shmem */
		val = MF_CFG_RD(bp, func_mf_config[func].e1hov_tag) &
				FUNC_MF_CFG_E1HOV_TAG_MASK;
		if (val != FUNC_MF_CFG_E1HOV_TAG_DEFAULT) {
			bp->mf_ov = val;
		} else {
			BNX2X_ERR("Got an SVID event, but no tag is configured in shmem\n");
			goto fail;
		}

		/* Configure new S-tag in LLH */
		REG_WR(bp, NIG_REG_LLH0_FUNC_VLAN_ID + BP_PORT(bp) * 8,
		       bp->mf_ov);

		/* Send Ramrod to update FW of change */
		__set_bit(BNX2X_F_UPDATE_SD_VLAN_TAG_CHNG,
			  &switch_update_params->changes);
		switch_update_params->vlan = bp->mf_ov;

		if (bnx2x_func_state_change(bp, &func_params) < 0) {
			BNX2X_ERR("Failed to configure FW of S-tag Change to %02x\n",
				  bp->mf_ov);
			goto fail;
		} else {
			DP(BNX2X_MSG_MCP, "Configured S-tag %02x\n",
			   bp->mf_ov);
		}
	} else {
		goto fail;
	}

	bnx2x_fw_command(bp, DRV_MSG_CODE_OEM_UPDATE_SVID_OK, 0);
	return;
fail:
	bnx2x_fw_command(bp, DRV_MSG_CODE_OEM_UPDATE_SVID_FAILURE, 0);
}