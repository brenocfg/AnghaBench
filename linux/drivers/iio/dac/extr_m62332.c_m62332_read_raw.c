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
struct m62332_data {int* raw; int /*<<< orphan*/  vcc; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 struct m62332_data* iio_priv (struct iio_dev*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m62332_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long mask)
{
	struct m62332_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		/* Corresponds to Vref / 2^(bits) */
		ret = regulator_get_voltage(data->vcc);
		if (ret < 0)
			return ret;

		*val = ret / 1000; /* mV */
		*val2 = 8;

		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_RAW:
		*val = data->raw[chan->channel];

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		*val = 1;

		return IIO_VAL_INT;
	default:
		break;
	}

	return -EINVAL;
}