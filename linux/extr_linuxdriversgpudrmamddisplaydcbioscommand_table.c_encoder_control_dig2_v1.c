#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bp_encoder_control {int dummy; } ;
struct bios_parser {TYPE_2__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_6__ {int /*<<< orphan*/  (* assign_control_parameter ) (TYPE_2__*,struct bp_encoder_control*,TYPE_1__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ DIG_ENCODER_CONTROL_PARAMETERS_V2 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  DIG2EncoderControl ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct bp_encoder_control*,TYPE_1__*) ; 

__attribute__((used)) static enum bp_result encoder_control_dig2_v1(
	struct bios_parser *bp,
	struct bp_encoder_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V2 params = {0};

	bp->cmd_helper->assign_control_parameter(bp->cmd_helper, cntl, &params);

	if (EXEC_BIOS_CMD_TABLE(DIG2EncoderControl, params))
		result = BP_RESULT_OK;

	return result;
}