#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  speed_step; int /*<<< orphan*/  filter; int /*<<< orphan*/  height_weight; } ;
struct mma9553_data {int stepcnt_enabled; int /*<<< orphan*/  mutex; TYPE_1__ conf; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBHEIGHT 135 
#define  IIO_CHAN_INFO_CALIBWEIGHT 134 
#define  IIO_CHAN_INFO_DEBOUNCE_COUNT 133 
#define  IIO_CHAN_INFO_DEBOUNCE_TIME 132 
#define  IIO_CHAN_INFO_ENABLE 131 
#define  IIO_CHAN_INFO_INT_TIME 130 
 int /*<<< orphan*/  IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z ; 
#define  IIO_STEPS 129 
#define  IIO_VELOCITY 128 
 int /*<<< orphan*/  MMA9553_MASK_CONF_FILTSTEP ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_FILTTIME ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_HEIGHT ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_SPDPRD ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_WEIGHT ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_FILTER ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_HEIGHT_WEIGHT ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_SPEED_STEP ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9551_set_power_state (int /*<<< orphan*/ ,int) ; 
 int mma9553_set_config (struct mma9553_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	int ret, tmp;

	switch (mask) {
	case IIO_CHAN_INFO_ENABLE:
		if (data->stepcnt_enabled == !!val)
			return 0;
		mutex_lock(&data->mutex);
		ret = mma9551_set_power_state(data->client, val);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}
		data->stepcnt_enabled = val;
		mutex_unlock(&data->mutex);
		return 0;
	case IIO_CHAN_INFO_CALIBHEIGHT:
		/* m to cm */
		tmp = val * 100 + val2 / 10000;
		if (tmp < 0 || tmp > 255)
			return -EINVAL;
		mutex_lock(&data->mutex);
		ret = mma9553_set_config(data,
					 MMA9553_REG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 tmp, MMA9553_MASK_CONF_HEIGHT);
		mutex_unlock(&data->mutex);
		return ret;
	case IIO_CHAN_INFO_CALIBWEIGHT:
		if (val < 0 || val > 255)
			return -EINVAL;
		mutex_lock(&data->mutex);
		ret = mma9553_set_config(data,
					 MMA9553_REG_CONF_HEIGHT_WEIGHT,
					 &data->conf.height_weight,
					 val, MMA9553_MASK_CONF_WEIGHT);
		mutex_unlock(&data->mutex);
		return ret;
	case IIO_CHAN_INFO_DEBOUNCE_COUNT:
		switch (chan->type) {
		case IIO_STEPS:
			/*
			 * Set to 0 to disable step filtering. If the value
			 * specified is greater than 6, then 6 will be used.
			 */
			if (val < 0)
				return -EINVAL;
			if (val > 6)
				val = 6;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
						 &data->conf.filter, val,
						 MMA9553_MASK_CONF_FILTSTEP);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_DEBOUNCE_TIME:
		switch (chan->type) {
		case IIO_STEPS:
			if (val < 0 || val > 127)
				return -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_FILTER,
						 &data->conf.filter, val,
						 MMA9553_MASK_CONF_FILTTIME);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_VELOCITY:
			if (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				return -EINVAL;
			/*
			 * If set to a value greater than 5, then 5 will be
			 * used. Warning: Do not set SPDPRD to 0 or 1 as
			 * this may cause undesirable behavior.
			 */
			if (val < 2)
				return -EINVAL;
			if (val > 5)
				val = 5;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data,
						 MMA9553_REG_CONF_SPEED_STEP,
						 &data->conf.speed_step, val,
						 MMA9553_MASK_CONF_SPDPRD);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}