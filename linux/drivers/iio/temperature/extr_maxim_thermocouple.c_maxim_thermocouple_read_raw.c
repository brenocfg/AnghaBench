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
struct maxim_thermocouple_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_MOD_TEMP_AMBIENT 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct maxim_thermocouple_data* iio_priv (struct iio_dev*) ; 
 int maxim_thermocouple_read (struct maxim_thermocouple_data*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int maxim_thermocouple_read_raw(struct iio_dev *indio_dev,
				       struct iio_chan_spec const *chan,
				       int *val, int *val2, long mask)
{
	struct maxim_thermocouple_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		ret = maxim_thermocouple_read(data, chan, val);
		iio_device_release_direct_mode(indio_dev);

		if (!ret)
			return IIO_VAL_INT;

		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->channel2) {
		case IIO_MOD_TEMP_AMBIENT:
			*val = 62;
			*val2 = 500000; /* 1000 * 0.0625 */
			ret = IIO_VAL_INT_PLUS_MICRO;
			break;
		default:
			*val = 250; /* 1000 * 0.25 */
			ret = IIO_VAL_INT;
		};
		break;
	}

	return ret;
}