#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_func_tx_start_params {int dummy; } ;
struct TYPE_2__ {struct bnx2x_func_tx_start_params tx_start; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_TX_START ; 
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_dcbx_fw_struct (struct bnx2x*,struct bnx2x_func_tx_start_params*) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int /*<<< orphan*/  bnx2x_panic () ; 

int bnx2x_dcbx_resume_hw_tx(struct bnx2x *bp)
{
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_func_tx_start_params *tx_params =
		&func_params.params.tx_start;
	int rc;

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_TX_START;

	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	bnx2x_dcbx_fw_struct(bp, tx_params);

	DP(BNX2X_MSG_DCB, "START TRAFFIC\n");

	rc = bnx2x_func_state_change(bp, &func_params);
	if (rc) {
		BNX2X_ERR("Unable to resume traffic after HW configuration\n");
		bnx2x_panic();
	}

	return rc;
}