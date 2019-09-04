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

/* Variables and functions */
#define  AXP813_BATT_V 129 
#define  AXP813_GPIO0_V 128 
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 

__attribute__((used)) static int axp813_adc_scale_voltage(int channel, int *val, int *val2)
{
	switch (channel) {
	case AXP813_GPIO0_V:
		*val = 0;
		*val2 = 800000;
		return IIO_VAL_INT_PLUS_MICRO;

	case AXP813_BATT_V:
		*val = 1;
		*val2 = 100000;
		return IIO_VAL_INT_PLUS_MICRO;

	default:
		return -EINVAL;
	}
}