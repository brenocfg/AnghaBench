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
struct audio {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ENABLED ; 
 int /*<<< orphan*/  AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL ; 
 int /*<<< orphan*/  AZ_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AZ_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_GATING_DISABLE ; 
 int /*<<< orphan*/  DC_LOGGER_INIT () ; 
 int /*<<< orphan*/  DC_LOG_HW_AUDIO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce_aud_az_disable(struct audio *audio)
{
	uint32_t value;
	DC_LOGGER_INIT();

	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	set_reg_field_value(value, 1,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	set_reg_field_value(value, 0,
		AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
		AUDIO_ENABLED);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);

	set_reg_field_value(value, 0,
			AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL,
			CLOCK_GATING_DISABLE);
	AZ_REG_WRITE(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL, value);
	value = AZ_REG_READ(AZALIA_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL);
	DC_LOG_HW_AUDIO("\n\t========= AUDIO:dce_aud_az_disable: index: %u  data: 0x%x\n",
			audio->inst, value);
}