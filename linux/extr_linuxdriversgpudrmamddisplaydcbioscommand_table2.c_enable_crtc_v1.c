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
typedef  int /*<<< orphan*/  uint8_t ;
struct enable_crtc_parameters {int /*<<< orphan*/  enable; int /*<<< orphan*/  crtc_id; int /*<<< orphan*/  member_0; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_2__ {scalar_t__ (* controller_id_to_atom ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,struct enable_crtc_parameters) ; 
 int /*<<< orphan*/  enablecrtc ; 
 scalar_t__ stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum bp_result enable_crtc_v1(
	struct bios_parser *bp,
	enum controller_id controller_id,
	bool enable)
{
	bool result = BP_RESULT_FAILURE;
	struct enable_crtc_parameters params = {0};
	uint8_t id;

	if (bp->cmd_helper->controller_id_to_atom(controller_id, &id))
		params.crtc_id = id;
	else
		return BP_RESULT_BADINPUT;

	if (enable)
		params.enable = ATOM_ENABLE;
	else
		params.enable = ATOM_DISABLE;

	if (EXEC_BIOS_CMD_TABLE(enablecrtc, params))
		result = BP_RESULT_OK;

	return result;
}