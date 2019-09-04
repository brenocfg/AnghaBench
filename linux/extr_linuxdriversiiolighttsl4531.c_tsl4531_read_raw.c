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
struct tsl4531_data {int int_time; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  TSL4531_DATA ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tsl4531_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int tsl4531_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct tsl4531_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_read_word_data(data->client,
			TSL4531_DATA);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		/* 0.. 1x, 1 .. 2x, 2 .. 4x */
		*val = 1 << data->int_time;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		if (data->int_time == 0)
			*val2 = 400000;
		else if (data->int_time == 1)
			*val2 = 200000;
		else if (data->int_time == 2)
			*val2 = 100000;
		else
			return -EINVAL;
		*val = 0;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}