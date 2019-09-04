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
struct mag3110_data {int ctrl_reg1; int /*<<< orphan*/  client; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_MAGN 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int MAG3110_CTRL_DR_SHIFT ; 
 int /*<<< orphan*/  MAG3110_DIE_TEMP ; 
 int /*<<< orphan*/  MAG3110_OFF_X ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mag3110_data* iio_priv (struct iio_dev*) ; 
 int mag3110_read (struct mag3110_data*,int /*<<< orphan*/ *) ; 
 int mag3110_request (struct mag3110_data*) ; 
 int** mag3110_samp_freq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int mag3110_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mag3110_data *data = iio_priv(indio_dev);
	__be16 buffer[3];
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		switch (chan->type) {
		case IIO_MAGN: /* in 0.1 uT / LSB */
			ret = mag3110_read(data, buffer);
			if (ret < 0)
				goto release;
			*val = sign_extend32(
				be16_to_cpu(buffer[chan->scan_index]), 15);
			ret = IIO_VAL_INT;
			break;
		case IIO_TEMP: /* in 1 C / LSB */
			mutex_lock(&data->lock);
			ret = mag3110_request(data);
			if (ret < 0) {
				mutex_unlock(&data->lock);
				goto release;
			}
			ret = i2c_smbus_read_byte_data(data->client,
				MAG3110_DIE_TEMP);
			mutex_unlock(&data->lock);
			if (ret < 0)
				goto release;
			*val = sign_extend32(ret, 7);
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
		}
release:
		iio_device_release_direct_mode(indio_dev);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_MAGN:
			*val = 0;
			*val2 = 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = 1000;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		i = data->ctrl_reg1 >> MAG3110_CTRL_DR_SHIFT;
		*val = mag3110_samp_freq[i][0];
		*val2 = mag3110_samp_freq[i][1];
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_read_word_swapped(data->client,
			MAG3110_OFF_X +	2 * chan->scan_index);
		if (ret < 0)
			return ret;
		*val = sign_extend32(ret >> 1, 14);
		return IIO_VAL_INT;
	}
	return -EINVAL;
}