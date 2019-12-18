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
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  IIO_TEMP ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int berlin2_adc_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int berlin2_adc_tsen_read (struct iio_dev*) ; 

__attribute__((used)) static int berlin2_adc_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan, int *val,
				int *val2, long mask)
{
	int temp;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type != IIO_VOLTAGE)
			return -EINVAL;

		*val = berlin2_adc_read(indio_dev, chan->channel);
		if (*val < 0)
			return *val;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_PROCESSED:
		if (chan->type != IIO_TEMP)
			return -EINVAL;

		temp = berlin2_adc_tsen_read(indio_dev);
		if (temp < 0)
			return temp;

		if (temp > 2047)
			temp -= 4096;

		/* Convert to milli Celsius */
		*val = ((temp * 100000) / 264 - 270000);
		return IIO_VAL_INT;
	default:
		break;
	}

	return -EINVAL;
}