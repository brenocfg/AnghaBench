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
typedef  int /*<<< orphan*/  uint32_t ;
struct dce_audio {int dummy; } ;
struct audio {scalar_t__ inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_RATE_CAPABILITIES ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL ; 
 int /*<<< orphan*/  AZ_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AZ_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKSTOP ; 
 int /*<<< orphan*/  CLOCK_GATING_DISABLE ; 
 struct dce_audio* DCE_AUD (struct audio*) ; 
 int /*<<< orphan*/  EPSS ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce_aud_hw_init(
		struct audio *audio)
{
	uint32_t value;
	struct dce_audio *aud = DCE_AUD(audio);

	/* we only need to program the following registers once, so we only do
	it for the inst 0*/
	if (audio->inst != 0)
		return;

	/* Suport R5 - 32khz
	 * Suport R6 - 44.1khz
	 * Suport R7 - 48khz
	 */
	/*disable clock gating before write to endpoint register*/
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 1,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
	REG_UPDATE(AZALIA_F0_CODEC_FUNCTION_PARAMETER_SUPPORTED_SIZE_RATES,
			AUDIO_RATE_CAPABILITIES, 0x70);

	/*Keep alive bit to verify HW block in BU. */
	REG_UPDATE_2(AZALIA_F0_CODEC_FUNCTION_PARAMETER_POWER_STATES,
			CLKSTOP, 1,
			EPSS, 1);
	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
}