#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bios_parser {int dummy; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
typedef  int /*<<< orphan*/  DAC_ENCODER_CONTROL_PS_ALLOCATION ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  DAC2EncoderControl ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_encoder_control_prepare_params (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result dac2_encoder_control_v1(
	struct bios_parser *bp,
	bool enable,
	uint32_t pixel_clock,
	uint8_t dac_standard)
{
	enum bp_result result = BP_RESULT_FAILURE;
	DAC_ENCODER_CONTROL_PS_ALLOCATION params;

	dac_encoder_control_prepare_params(
		&params,
		enable,
		pixel_clock,
		dac_standard);

	if (EXEC_BIOS_CMD_TABLE(DAC2EncoderControl, params))
		result = BP_RESULT_OK;

	return result;
}