#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bios_parser {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_3__ {int /*<<< orphan*/  ucAction; } ;
typedef  TYPE_1__ DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  DAC1OutputControl ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_1__) ; 

__attribute__((used)) static enum bp_result dac1_output_control_v1(
	struct bios_parser *bp, bool enable)
{
	enum bp_result result = BP_RESULT_FAILURE;
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION params;

	if (enable)
		params.ucAction = ATOM_ENABLE;
	else
		params.ucAction = ATOM_DISABLE;

	if (EXEC_BIOS_CMD_TABLE(DAC1OutputControl, params))
		result = BP_RESULT_OK;

	return result;
}