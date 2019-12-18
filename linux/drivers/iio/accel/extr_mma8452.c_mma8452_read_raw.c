#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mma8452_data {int data_cfg; int /*<<< orphan*/  client; TYPE_2__* chip_info; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {int shift; int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {size_t scan_index; TYPE_1__ scan_type; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int** mma_scales; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 133 
#define  IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY 132 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int MMA8452_DATA_CFG_FS_MASK ; 
 int MMA8452_DATA_CFG_HPF_MASK ; 
 size_t MMA8452_OFF_X ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,size_t) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 int mma8452_get_power_mode (struct mma8452_data*) ; 
 int** mma8452_os_ratio ; 
 int mma8452_read (struct mma8452_data*,int /*<<< orphan*/ *) ; 
 int mma8452_read_hp_filter (struct mma8452_data*,int*,int*) ; 
 int** mma8452_samp_freq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int mma8452_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mma8452_data *data = iio_priv(indio_dev);
	__be16 buffer[3];
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;

		mutex_lock(&data->lock);
		ret = mma8452_read(data, buffer);
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		if (ret < 0)
			return ret;

		*val = sign_extend32(be16_to_cpu(
			buffer[chan->scan_index]) >> chan->scan_type.shift,
			chan->scan_type.realbits - 1);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		i = data->data_cfg & MMA8452_DATA_CFG_FS_MASK;
		*val = data->chip_info->mma_scales[i][0];
		*val2 = data->chip_info->mma_scales[i][1];

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		i = mma8452_get_odr_index(data);
		*val = mma8452_samp_freq[i][0];
		*val2 = mma8452_samp_freq[i][1];

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_read_byte_data(data->client,
					       MMA8452_OFF_X +
					       chan->scan_index);
		if (ret < 0)
			return ret;

		*val = sign_extend32(ret, 7);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		if (data->data_cfg & MMA8452_DATA_CFG_HPF_MASK) {
			ret = mma8452_read_hp_filter(data, val, val2);
			if (ret < 0)
				return ret;
		} else {
			*val = 0;
			*val2 = 0;
		}

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = mma8452_get_power_mode(data);
		if (ret < 0)
			return ret;

		i = mma8452_get_odr_index(data);

		*val = mma8452_os_ratio[ret][i];
		return IIO_VAL_INT;
	}

	return -EINVAL;
}