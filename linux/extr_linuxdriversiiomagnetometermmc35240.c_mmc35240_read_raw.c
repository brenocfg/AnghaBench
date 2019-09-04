#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc35240_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 unsigned int MMC35240_CTRL1_BW_MASK ; 
 unsigned int MMC35240_CTRL1_BW_SHIFT ; 
 int /*<<< orphan*/  MMC35240_REG_CTRL1 ; 
 struct mmc35240_data* iio_priv (struct iio_dev*) ; 
 int mmc35240_raw_to_mgauss (struct mmc35240_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int mmc35240_read_measurement (struct mmc35240_data*,int /*<<< orphan*/ *) ; 
 TYPE_1__* mmc35240_samp_freq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mmc35240_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int *val,
			     int *val2, long mask)
{
	struct mmc35240_data *data = iio_priv(indio_dev);
	int ret, i;
	unsigned int reg;
	__le16 buf[3];

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		ret = mmc35240_read_measurement(data, buf);
		mutex_unlock(&data->mutex);
		if (ret < 0)
			return ret;
		ret = mmc35240_raw_to_mgauss(data, chan->address, buf, val);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = regmap_read(data->regmap, MMC35240_REG_CTRL1, &reg);
		mutex_unlock(&data->mutex);
		if (ret < 0)
			return ret;

		i = (reg & MMC35240_CTRL1_BW_MASK) >> MMC35240_CTRL1_BW_SHIFT;
		if (i < 0 || i >= ARRAY_SIZE(mmc35240_samp_freq))
			return -EINVAL;

		*val = mmc35240_samp_freq[i].val;
		*val2 = mmc35240_samp_freq[i].val2;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}