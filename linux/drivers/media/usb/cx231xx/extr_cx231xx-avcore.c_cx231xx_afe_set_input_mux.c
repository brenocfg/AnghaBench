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
typedef  int u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_INPUT_CH1 ; 
 int /*<<< orphan*/  ADC_INPUT_CH2 ; 
 int /*<<< orphan*/  ADC_INPUT_CH3 ; 
 int INPUT_SEL_MASK ; 
 int afe_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int afe_write_byte (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

int cx231xx_afe_set_input_mux(struct cx231xx *dev, u32 input_mux)
{
	u8 ch1_setting = (u8) input_mux;
	u8 ch2_setting = (u8) (input_mux >> 8);
	u8 ch3_setting = (u8) (input_mux >> 16);
	int status = 0;
	u8 value = 0;

	if (ch1_setting != 0) {
		status = afe_read_byte(dev, ADC_INPUT_CH1, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch1_setting - 1) << 4;
		value &= 0xff;
		status = afe_write_byte(dev, ADC_INPUT_CH1, value);
	}

	if (ch2_setting != 0) {
		status = afe_read_byte(dev, ADC_INPUT_CH2, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch2_setting - 1) << 4;
		value &= 0xff;
		status = afe_write_byte(dev, ADC_INPUT_CH2, value);
	}

	/* For ch3_setting, the value to put in the register is
	   7 less than the input number */
	if (ch3_setting != 0) {
		status = afe_read_byte(dev, ADC_INPUT_CH3, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch3_setting - 1) << 4;
		value &= 0xff;
		status = afe_write_byte(dev, ADC_INPUT_CH3, value);
	}

	return status;
}