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
#define  AXP20X_ACIN_V 133 
#define  AXP20X_BATT_V 132 
#define  AXP20X_GPIO0_V 131 
#define  AXP20X_GPIO1_V 130 
#define  AXP20X_IPSOUT_V 129 
#define  AXP20X_VBUS_V 128 
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 

__attribute__((used)) static int axp20x_adc_scale_voltage(int channel, int *val, int *val2)
{
	switch (channel) {
	case AXP20X_ACIN_V:
	case AXP20X_VBUS_V:
		*val = 1;
		*val2 = 700000;
		return IIO_VAL_INT_PLUS_MICRO;

	case AXP20X_GPIO0_V:
	case AXP20X_GPIO1_V:
		*val = 0;
		*val2 = 500000;
		return IIO_VAL_INT_PLUS_MICRO;

	case AXP20X_BATT_V:
		*val = 1;
		*val2 = 100000;
		return IIO_VAL_INT_PLUS_MICRO;

	case AXP20X_IPSOUT_V:
		*val = 1;
		*val2 = 400000;
		return IIO_VAL_INT_PLUS_MICRO;

	default:
		return -EINVAL;
	}
}