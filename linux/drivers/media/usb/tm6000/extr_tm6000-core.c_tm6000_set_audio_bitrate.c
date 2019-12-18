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
typedef  int u8 ;
struct tm6000_core {int audio_bitrate; scalar_t__ dev_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TM6000_REQ07_REB_VADC_AADC_MODE ; 
 scalar_t__ TM6010 ; 
 int /*<<< orphan*/  TM6010_REQ08_R0A_A_I2S_MOD ; 
 int /*<<< orphan*/  TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG ; 
 int tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int) ; 
 int tm6000_set_reg_mask (struct tm6000_core*,int /*<<< orphan*/ ,int,int) ; 

int tm6000_set_audio_bitrate(struct tm6000_core *dev, int bitrate)
{
	int val = 0;
	u8 areg_f0 = 0x60; /* ADC MCLK = 250 Fs */
	u8 areg_0a = 0x91; /* SIF 48KHz */

	switch (bitrate) {
	case 48000:
		areg_f0 = 0x60; /* ADC MCLK = 250 Fs */
		areg_0a = 0x91; /* SIF 48KHz */
		dev->audio_bitrate = bitrate;
		break;
	case 32000:
		areg_f0 = 0x00; /* ADC MCLK = 375 Fs */
		areg_0a = 0x90; /* SIF 32KHz */
		dev->audio_bitrate = bitrate;
		break;
	default:
		return -EINVAL;
	}


	/* enable I2S, if we use sif or external I2S device */
	if (dev->dev_type == TM6010) {
		val = tm6000_set_reg(dev, TM6010_REQ08_R0A_A_I2S_MOD, areg_0a);
		if (val < 0)
			return val;

		val = tm6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
							areg_f0, 0xf0);
		if (val < 0)
			return val;
	} else {
		val = tm6000_set_reg_mask(dev, TM6000_REQ07_REB_VADC_AADC_MODE,
							areg_f0, 0xf0);
		if (val < 0)
			return val;
	}
	return 0;
}