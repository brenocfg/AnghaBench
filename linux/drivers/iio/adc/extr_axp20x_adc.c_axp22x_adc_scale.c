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
struct iio_chan_spec {int type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP22X_BATT_V ; 
 int EINVAL ; 
#define  IIO_CURRENT 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 

__attribute__((used)) static int axp22x_adc_scale(struct iio_chan_spec const *chan, int *val,
			    int *val2)
{
	switch (chan->type) {
	case IIO_VOLTAGE:
		if (chan->channel != AXP22X_BATT_V)
			return -EINVAL;

		*val = 1;
		*val2 = 100000;
		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CURRENT:
		*val = 0;
		*val2 = 500000;
		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_TEMP:
		*val = 100;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}