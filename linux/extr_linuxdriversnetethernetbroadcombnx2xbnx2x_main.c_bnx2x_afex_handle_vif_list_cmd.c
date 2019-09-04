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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x_func_afex_viflists_params {scalar_t__ func_to_clear; scalar_t__ func_bit_map; int /*<<< orphan*/  vif_list_index; scalar_t__ afex_vif_list_command; } ;
struct TYPE_2__ {struct bnx2x_func_afex_viflists_params afex_viflists; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_AFEX_VIFLISTS ; 
 int /*<<< orphan*/  DRV_MSG_CODE_AFEX_LISTGET_ACK ; 
 int /*<<< orphan*/  DRV_MSG_CODE_AFEX_LISTSET_ACK ; 
 scalar_t__ VIF_LIST_RULE_GET ; 
 scalar_t__ VIF_LIST_RULE_SET ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_afex_handle_vif_list_cmd(struct bnx2x *bp, u8 cmd_type,
					  u16 vif_index, u8 func_bit_map)
{
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_func_afex_viflists_params *update_params =
		&func_params.params.afex_viflists;
	int rc;
	u32 drv_msg_code;

	/* validate only LIST_SET and LIST_GET are received from switch */
	if ((cmd_type != VIF_LIST_RULE_GET) && (cmd_type != VIF_LIST_RULE_SET))
		BNX2X_ERR("BUG! afex_handle_vif_list_cmd invalid type 0x%x\n",
			  cmd_type);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_AFEX_VIFLISTS;

	/* set parameters according to cmd_type */
	update_params->afex_vif_list_command = cmd_type;
	update_params->vif_list_index = vif_index;
	update_params->func_bit_map =
		(cmd_type == VIF_LIST_RULE_GET) ? 0 : func_bit_map;
	update_params->func_to_clear = 0;
	drv_msg_code =
		(cmd_type == VIF_LIST_RULE_GET) ?
		DRV_MSG_CODE_AFEX_LISTGET_ACK :
		DRV_MSG_CODE_AFEX_LISTSET_ACK;

	/* if ramrod can not be sent, respond to MCP immediately for
	 * SET and GET requests (other are not triggered from MCP)
	 */
	rc = bnx2x_func_state_change(bp, &func_params);
	if (rc < 0)
		bnx2x_fw_command(bp, drv_msg_code, 0);

	return 0;
}