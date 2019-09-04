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
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int sun4i_gpadc_adc_read (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 int sun4i_gpadc_temp_offset (struct iio_dev*,int*) ; 
 int sun4i_gpadc_temp_read (struct iio_dev*,int*) ; 
 int sun4i_gpadc_temp_scale (struct iio_dev*,int*) ; 

__attribute__((used)) static int sun4i_gpadc_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan, int *val,
				int *val2, long mask)
{
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		ret = sun4i_gpadc_temp_offset(indio_dev, val);
		if (ret)
			return ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_VOLTAGE)
			ret = sun4i_gpadc_adc_read(indio_dev, chan->channel,
						   val);
		else
			ret = sun4i_gpadc_temp_read(indio_dev, val);

		if (ret)
			return ret;

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_VOLTAGE) {
			/* 3000mV / 4096 * raw */
			*val = 0;
			*val2 = 732421875;
			return IIO_VAL_INT_PLUS_NANO;
		}

		ret = sun4i_gpadc_temp_scale(indio_dev, val);
		if (ret)
			return ret;

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}