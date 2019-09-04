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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct bh1750_data {int mtreg; int /*<<< orphan*/  lock; struct bh1750_chip_info* chip_info; } ;
struct bh1750_chip_info {int mtreg_to_scale; int mtreg_to_usec; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_LIGHT 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int bh1750_read (struct bh1750_data*,int*) ; 
 struct bh1750_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1750_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	int ret, tmp;
	struct bh1750_data *data = iio_priv(indio_dev);
	const struct bh1750_chip_info *chip_info = data->chip_info;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			mutex_lock(&data->lock);
			ret = bh1750_read(data, val);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		tmp = chip_info->mtreg_to_scale / data->mtreg;
		*val = tmp / 1000000;
		*val2 = tmp % 1000000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = chip_info->mtreg_to_usec * data->mtreg;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}