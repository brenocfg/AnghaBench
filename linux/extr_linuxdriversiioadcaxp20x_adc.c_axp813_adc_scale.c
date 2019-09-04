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
 int EINVAL ; 
#define  IIO_CURRENT 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 int axp813_adc_scale_voltage (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int axp813_adc_scale(struct iio_chan_spec const *chan, int *val,
			    int *val2)
{
	switch (chan->type) {
	case IIO_VOLTAGE:
		return axp813_adc_scale_voltage(chan->channel, val, val2);

	case IIO_CURRENT:
		*val = 1;
		return IIO_VAL_INT;

	case IIO_TEMP:
		*val = 100;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}