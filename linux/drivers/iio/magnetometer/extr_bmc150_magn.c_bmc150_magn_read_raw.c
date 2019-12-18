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
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  channel2; } ;
struct bmc150_magn_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mutex; } ;
typedef  int s32 ;

/* Variables and functions */
 int AXIS_XYZ_MAX ; 
 int BMC150_MAGN_REGVAL_TO_REPXY (int) ; 
 int BMC150_MAGN_REGVAL_TO_REPZ (int) ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_XY ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_REP_Z ; 
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 134 
#define  IIO_CHAN_INFO_RAW 133 
#define  IIO_CHAN_INFO_SAMP_FREQ 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_MOD_X 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int bmc150_magn_get_odr (struct bmc150_magn_data*,int*) ; 
 int bmc150_magn_read_xyz (struct bmc150_magn_data*,int*) ; 
 int bmc150_magn_set_power_state (struct bmc150_magn_data*,int) ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bmc150_magn_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret, tmp;
	s32 values[AXIS_XYZ_MAX];

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		mutex_lock(&data->mutex);

		ret = bmc150_magn_set_power_state(data, true);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}

		ret = bmc150_magn_read_xyz(data, values);
		if (ret < 0) {
			bmc150_magn_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		*val = values[chan->scan_index];

		ret = bmc150_magn_set_power_state(data, false);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}

		mutex_unlock(&data->mutex);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		/*
		 * The API/driver performs an off-chip temperature
		 * compensation and outputs x/y/z magnetic field data in
		 * 16 LSB/uT to the upper application layer.
		 */
		*val = 0;
		*val2 = 625;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = bmc150_magn_get_odr(data, val);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->channel2) {
		case IIO_MOD_X:
		case IIO_MOD_Y:
			ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_XY,
					  &tmp);
			if (ret < 0)
				return ret;
			*val = BMC150_MAGN_REGVAL_TO_REPXY(tmp);
			return IIO_VAL_INT;
		case IIO_MOD_Z:
			ret = regmap_read(data->regmap, BMC150_MAGN_REG_REP_Z,
					  &tmp);
			if (ret < 0)
				return ret;
			*val = BMC150_MAGN_REGVAL_TO_REPZ(tmp);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}