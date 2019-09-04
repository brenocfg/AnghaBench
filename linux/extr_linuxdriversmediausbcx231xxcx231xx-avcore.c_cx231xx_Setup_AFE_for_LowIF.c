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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CTRL_DAC1_CH3 ; 
 int /*<<< orphan*/  ADC_CTRL_DAC23_CH3 ; 
 int /*<<< orphan*/  ADC_DCSERVO_DEM_CH3 ; 
 int /*<<< orphan*/  ADC_FB_FRCRST_CH3 ; 
 int /*<<< orphan*/  ADC_INPUT_CH3 ; 
 int /*<<< orphan*/  ADC_NTF_PRECLMP_EN_CH3 ; 
 int /*<<< orphan*/  ADC_PWRDN_CLAMP_CH3 ; 
 int /*<<< orphan*/  ADC_STATUS2_CH3 ; 
 int /*<<< orphan*/  afe_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  afe_write_byte (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

void cx231xx_Setup_AFE_for_LowIF(struct cx231xx *dev)

{
	u8 value = 0;

	afe_read_byte(dev, ADC_STATUS2_CH3, &value);
	value = (value & 0xFE)|0x01;
	afe_write_byte(dev, ADC_STATUS2_CH3, value);

	afe_read_byte(dev, ADC_STATUS2_CH3, &value);
	value = (value & 0xFE)|0x00;
	afe_write_byte(dev, ADC_STATUS2_CH3, value);


/*
	config colibri to lo-if mode

	FIXME: ntf_mode = 2'b00 by default. But set 0x1 would reduce
		the diff IF input by half,

		for low-if agc defect
*/

	afe_read_byte(dev, ADC_NTF_PRECLMP_EN_CH3, &value);
	value = (value & 0xFC)|0x00;
	afe_write_byte(dev, ADC_NTF_PRECLMP_EN_CH3, value);

	afe_read_byte(dev, ADC_INPUT_CH3, &value);
	value = (value & 0xF9)|0x02;
	afe_write_byte(dev, ADC_INPUT_CH3, value);

	afe_read_byte(dev, ADC_FB_FRCRST_CH3, &value);
	value = (value & 0xFB)|0x04;
	afe_write_byte(dev, ADC_FB_FRCRST_CH3, value);

	afe_read_byte(dev, ADC_DCSERVO_DEM_CH3, &value);
	value = (value & 0xFC)|0x03;
	afe_write_byte(dev, ADC_DCSERVO_DEM_CH3, value);

	afe_read_byte(dev, ADC_CTRL_DAC1_CH3, &value);
	value = (value & 0xFB)|0x04;
	afe_write_byte(dev, ADC_CTRL_DAC1_CH3, value);

	afe_read_byte(dev, ADC_CTRL_DAC23_CH3, &value);
	value = (value & 0xF8)|0x06;
	afe_write_byte(dev, ADC_CTRL_DAC23_CH3, value);

	afe_read_byte(dev, ADC_CTRL_DAC23_CH3, &value);
	value = (value & 0x8F)|0x40;
	afe_write_byte(dev, ADC_CTRL_DAC23_CH3, value);

	afe_read_byte(dev, ADC_PWRDN_CLAMP_CH3, &value);
	value = (value & 0xDF)|0x20;
	afe_write_byte(dev, ADC_PWRDN_CLAMP_CH3, value);
}