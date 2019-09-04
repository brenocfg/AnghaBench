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
struct dc_bios {int dummy; } ;
struct TYPE_2__ {int (* enable_disp_power_gating ) (struct bios_parser*,int,int) ;} ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
typedef  enum bp_pipe_control_action { ____Placeholder_bp_pipe_control_action } bp_pipe_control_action ;

/* Variables and functions */
 struct bios_parser* BP_FROM_DCB (struct dc_bios*) ; 
 int BP_RESULT_FAILURE ; 
 int stub1 (struct bios_parser*,int,int) ; 

__attribute__((used)) static enum bp_result bios_parser_enable_disp_power_gating(
	struct dc_bios *dcb,
	enum controller_id controller_id,
	enum bp_pipe_control_action action)
{
	struct bios_parser *bp = BP_FROM_DCB(dcb);

	if (!bp->cmd_tbl.enable_disp_power_gating)
		return BP_RESULT_FAILURE;

	return bp->cmd_tbl.enable_disp_power_gating(bp, controller_id,
		action);
}