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
#define  DA9150_GPADC_CHAN_TJUNC_CORE 130 
#define  DA9150_GPADC_CHAN_TJUNC_OVP 129 
#define  DA9150_GPADC_CHAN_VBAT 128 
 int EINVAL ; 
 int IIO_VAL_FRACTIONAL ; 

__attribute__((used)) static int da9150_gpadc_read_scale(int channel, int *val, int *val2)
{
	switch (channel) {
	case DA9150_GPADC_CHAN_VBAT:
		*val = 2932;
		*val2 = 1000;
		return IIO_VAL_FRACTIONAL;
	case DA9150_GPADC_CHAN_TJUNC_CORE:
	case DA9150_GPADC_CHAN_TJUNC_OVP:
		*val = 1000000;
		*val2 = 4420;
		return IIO_VAL_FRACTIONAL;
	default:
		return -EINVAL;
	}
}