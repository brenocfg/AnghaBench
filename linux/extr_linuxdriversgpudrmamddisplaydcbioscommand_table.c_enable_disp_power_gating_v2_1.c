#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
typedef  enum bp_pipe_control_action { ____Placeholder_bp_pipe_control_action } bp_pipe_control_action ;
struct TYPE_5__ {int /*<<< orphan*/  ucEnable; int /*<<< orphan*/  ucDispPipeId; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disp_power_gating_action_to_atom ) (int) ;scalar_t__ (* controller_id_to_atom ) (int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ ENABLE_DISP_POWER_GATING_PS_ALLOCATION ;

/* Variables and functions */
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  EnableDispPowerGating ; 
 scalar_t__ stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static enum bp_result enable_disp_power_gating_v2_1(
	struct bios_parser *bp,
	enum controller_id crtc_id,
	enum bp_pipe_control_action action)
{
	enum bp_result result = BP_RESULT_FAILURE;

	ENABLE_DISP_POWER_GATING_PS_ALLOCATION params = {0};
	uint8_t atom_crtc_id;

	if (bp->cmd_helper->controller_id_to_atom(crtc_id, &atom_crtc_id))
		params.ucDispPipeId = atom_crtc_id;
	else
		return BP_RESULT_BADINPUT;

	params.ucEnable =
			bp->cmd_helper->disp_power_gating_action_to_atom(action);

	if (EXEC_BIOS_CMD_TABLE(EnableDispPowerGating, params))
		result = BP_RESULT_OK;

	return result;
}