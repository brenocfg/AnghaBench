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
struct mmc35240_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  MMC35240_CTRL1_BW_MASK ; 
 int MMC35240_CTRL1_BW_SHIFT ; 
 int /*<<< orphan*/  MMC35240_REG_CTRL1 ; 
 struct mmc35240_data* iio_priv (struct iio_dev*) ; 
 int mmc35240_get_samp_freq_index (struct mmc35240_data*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc35240_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan, int val,
			      int val2, long mask)
{
	struct mmc35240_data *data = iio_priv(indio_dev);
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		i = mmc35240_get_samp_freq_index(data, val, val2);
		if (i < 0)
			return -EINVAL;
		mutex_lock(&data->mutex);
		ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL1,
					 MMC35240_CTRL1_BW_MASK,
					 i << MMC35240_CTRL1_BW_SHIFT);
		mutex_unlock(&data->mutex);
		return ret;
	default:
		return -EINVAL;
	}
}