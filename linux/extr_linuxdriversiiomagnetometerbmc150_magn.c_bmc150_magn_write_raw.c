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
struct iio_chan_spec {int /*<<< orphan*/  channel2; } ;
struct bmc150_magn_data {int max_odr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_DATAMASK ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_XY ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_Z ; 
 int /*<<< orphan*/  BMC150_MAGN_REPXY_TO_REGVAL (int) ; 
 int /*<<< orphan*/  BMC150_MAGN_REPZ_TO_REGVAL (int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_MOD_X 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 int bmc150_magn_set_max_odr (struct bmc150_magn_data*,int,int,int /*<<< orphan*/ ) ; 
 int bmc150_magn_set_odr (struct bmc150_magn_data*,int) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmc150_magn_write_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int val, int val2, long mask)
{
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val > data->max_odr)
			return -EINVAL;
		mutex_lock(&data->mutex);
		ret = bmc150_magn_set_odr(data, val);
		mutex_unlock(&data->mutex);
		return ret;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->channel2) {
		case IIO_MOD_X:
		case IIO_MOD_Y:
			if (val < 1 || val > 511)
				return -EINVAL;
			mutex_lock(&data->mutex);
			ret = bmc150_magn_set_max_odr(data, val, 0, 0);
			if (ret < 0) {
				mutex_unlock(&data->mutex);
				return ret;
			}
			ret = regmap_update_bits(data->regmap,
						 BMC150_MAGN_REG_REP_XY,
						 BMC150_MAGN_REG_REP_DATAMASK,
						 BMC150_MAGN_REPXY_TO_REGVAL
						 (val));
			mutex_unlock(&data->mutex);
			return ret;
		case IIO_MOD_Z:
			if (val < 1 || val > 256)
				return -EINVAL;
			mutex_lock(&data->mutex);
			ret = bmc150_magn_set_max_odr(data, 0, val, 0);
			if (ret < 0) {
				mutex_unlock(&data->mutex);
				return ret;
			}
			ret = regmap_update_bits(data->regmap,
						 BMC150_MAGN_REG_REP_Z,
						 BMC150_MAGN_REG_REP_DATAMASK,
						 BMC150_MAGN_REPZ_TO_REGVAL
						 (val));
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}