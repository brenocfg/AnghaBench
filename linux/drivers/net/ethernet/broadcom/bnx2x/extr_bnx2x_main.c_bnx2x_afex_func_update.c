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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct bnx2x_func_afex_update_params {int /*<<< orphan*/  allowed_priorities; void* afex_default_vlan; void* vif_id; } ;
struct TYPE_2__ {struct bnx2x_func_afex_update_params afex_update; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_F_CMD_AFEX_UPDATE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_AFEX_VIFSET_ACK ; 
 scalar_t__ bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_afex_func_update(struct bnx2x *bp, u16 vifid,
				  u16 vlan_val, u8 allowed_prio)
{
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_func_afex_update_params *f_update_params =
		&func_params.params.afex_update;

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_AFEX_UPDATE;

	/* no need to wait for RAMROD completion, so don't
	 * set RAMROD_COMP_WAIT flag
	 */

	f_update_params->vif_id = vifid;
	f_update_params->afex_default_vlan = vlan_val;
	f_update_params->allowed_priorities = allowed_prio;

	/* if ramrod can not be sent, response to MCP immediately */
	if (bnx2x_func_state_change(bp, &func_params) < 0)
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_VIFSET_ACK, 0);

	return 0;
}