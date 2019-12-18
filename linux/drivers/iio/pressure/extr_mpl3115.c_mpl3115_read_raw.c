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
typedef  int /*<<< orphan*/  u8 ;
struct mpl3115_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  MPL3115_OUT_PRESS ; 
 int /*<<< orphan*/  MPL3115_OUT_TEMP ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mpl3115_data* iio_priv (struct iio_dev*) ; 
 int mpl3115_request (struct mpl3115_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int mpl3115_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mpl3115_data *data = iio_priv(indio_dev);
	__be32 tmp = 0;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		switch (chan->type) {
		case IIO_PRESSURE: /* in 0.25 pascal / LSB */
			mutex_lock(&data->lock);
			ret = mpl3115_request(data);
			if (ret < 0) {
				mutex_unlock(&data->lock);
				break;
			}
			ret = i2c_smbus_read_i2c_block_data(data->client,
				MPL3115_OUT_PRESS, 3, (u8 *) &tmp);
			mutex_unlock(&data->lock);
			if (ret < 0)
				break;
			*val = be32_to_cpu(tmp) >> 12;
			ret = IIO_VAL_INT;
			break;
		case IIO_TEMP: /* in 0.0625 celsius / LSB */
			mutex_lock(&data->lock);
			ret = mpl3115_request(data);
			if (ret < 0) {
				mutex_unlock(&data->lock);
				break;
			}
			ret = i2c_smbus_read_i2c_block_data(data->client,
				MPL3115_OUT_TEMP, 2, (u8 *) &tmp);
			mutex_unlock(&data->lock);
			if (ret < 0)
				break;
			*val = sign_extend32(be32_to_cpu(tmp) >> 20, 11);
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
			break;
		}

		iio_device_release_direct_mode(indio_dev);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_PRESSURE:
			*val = 0;
			*val2 = 250; /* want kilopascal */
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = 0;
			*val2 = 62500;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	}
	return -EINVAL;
}