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
struct tcs3414_data {int gain; size_t timing; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int TCS3414_GAIN_MASK ; 
 int TCS3414_GAIN_SHIFT ; 
 size_t TCS3414_INTEG_MASK ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct tcs3414_data* iio_priv (struct iio_dev*) ; 
 int tcs3414_req_data (struct tcs3414_data*) ; 
 int** tcs3414_scales ; 
 int* tcs3414_times ; 

__attribute__((used)) static int tcs3414_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct tcs3414_data *data = iio_priv(indio_dev);
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		ret = tcs3414_req_data(data);
		if (ret < 0) {
			iio_device_release_direct_mode(indio_dev);
			return ret;
		}
		ret = i2c_smbus_read_word_data(data->client, chan->address);
		iio_device_release_direct_mode(indio_dev);
		if (ret < 0)
			return ret;
		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		i = (data->gain & TCS3414_GAIN_MASK) >> TCS3414_GAIN_SHIFT;
		*val = tcs3414_scales[i][0];
		*val2 = tcs3414_scales[i][1];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = tcs3414_times[data->timing & TCS3414_INTEG_MASK] * 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}