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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 int axp20x_adc_offset_voltage (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int axp20x_adc_offset(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int *val)
{
	switch (chan->type) {
	case IIO_VOLTAGE:
		return axp20x_adc_offset_voltage(indio_dev, chan->channel, val);

	case IIO_TEMP:
		*val = -1447;
		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}