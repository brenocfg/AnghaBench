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
typedef  void* u8 ;
typedef  int u16 ;
struct TYPE_2__ {int height_weight; int filter; int speed_step; } ;
struct mma9553_data {int stepcnt_enabled; TYPE_1__ conf; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 142 
#define  IIO_ACTIVITY 141 
#define  IIO_CHAN_INFO_CALIBHEIGHT 140 
#define  IIO_CHAN_INFO_CALIBWEIGHT 139 
#define  IIO_CHAN_INFO_DEBOUNCE_COUNT 138 
#define  IIO_CHAN_INFO_DEBOUNCE_TIME 137 
#define  IIO_CHAN_INFO_ENABLE 136 
#define  IIO_CHAN_INFO_INT_TIME 135 
#define  IIO_CHAN_INFO_PROCESSED 134 
#define  IIO_CHAN_INFO_RAW 133 
#define  IIO_CHAN_INFO_SCALE 132 
#define  IIO_DISTANCE 131 
#define  IIO_ENERGY 130 
 int /*<<< orphan*/  IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z ; 
#define  IIO_STEPS 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VELOCITY 128 
 int /*<<< orphan*/  MMA9553_MASK_CONF_FILTSTEP ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_FILTTIME ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_HEIGHT ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_SPDPRD ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_WEIGHT ; 
 int /*<<< orphan*/  MMA9553_MASK_STATUS_ACTIVITY ; 
 int /*<<< orphan*/  MMA9553_REG_CALORIES ; 
 int /*<<< orphan*/  MMA9553_REG_DISTANCE ; 
 int /*<<< orphan*/  MMA9553_REG_SPEED ; 
 int /*<<< orphan*/  MMA9553_REG_STATUS ; 
 int /*<<< orphan*/  MMA9553_REG_STEPCNT ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9551_read_accel_chan (int /*<<< orphan*/ ,struct iio_chan_spec const*,int*,int*) ; 
 int mma9551_read_accel_scale (int*,int*) ; 
 int /*<<< orphan*/  mma9553_activity_to_mod (void*) ; 
 void* mma9553_get_bits (int,int /*<<< orphan*/ ) ; 
 int mma9553_read_status_word (struct mma9553_data*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	int ret;
	u16 tmp;
	u8 activity;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_STEPS:
			ret = mma9553_read_status_word(data,
						       MMA9553_REG_STEPCNT,
						       &tmp);
			if (ret < 0)
				return ret;
			*val = tmp;
			return IIO_VAL_INT;
		case IIO_DISTANCE:
			ret = mma9553_read_status_word(data,
						       MMA9553_REG_DISTANCE,
						       &tmp);
			if (ret < 0)
				return ret;
			*val = tmp;
			return IIO_VAL_INT;
		case IIO_ACTIVITY:
			ret = mma9553_read_status_word(data,
						       MMA9553_REG_STATUS,
						       &tmp);
			if (ret < 0)
				return ret;

			activity =
			    mma9553_get_bits(tmp, MMA9553_MASK_STATUS_ACTIVITY);

			/*
			 * The device does not support confidence value levels,
			 * so we will always have 100% for current activity and
			 * 0% for the others.
			 */
			if (chan->channel2 == mma9553_activity_to_mod(activity))
				*val = 100;
			else
				*val = 0;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_VELOCITY:	/* m/h */
			if (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				return -EINVAL;
			ret = mma9553_read_status_word(data,
						       MMA9553_REG_SPEED,
						       &tmp);
			if (ret < 0)
				return ret;
			*val = tmp;
			return IIO_VAL_INT;
		case IIO_ENERGY:	/* Cal or kcal */
			ret = mma9553_read_status_word(data,
						       MMA9553_REG_CALORIES,
						       &tmp);
			if (ret < 0)
				return ret;
			*val = tmp;
			return IIO_VAL_INT;
		case IIO_ACCEL:
			mutex_lock(&data->mutex);
			ret = mma9551_read_accel_chan(data->client,
						      chan, val, val2);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VELOCITY:	/* m/h to m/s */
			if (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				return -EINVAL;
			*val = 0;
			*val2 = 277;	/* 0.000277 */
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ENERGY:	/* Cal or kcal to J */
			*val = 4184;
			return IIO_VAL_INT;
		case IIO_ACCEL:
			return mma9551_read_accel_scale(val, val2);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_ENABLE:
		*val = data->stepcnt_enabled;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBHEIGHT:
		tmp = mma9553_get_bits(data->conf.height_weight,
				       MMA9553_MASK_CONF_HEIGHT);
		*val = tmp / 100;	/* cm to m */
		*val2 = (tmp % 100) * 10000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_CALIBWEIGHT:
		*val = mma9553_get_bits(data->conf.height_weight,
					MMA9553_MASK_CONF_WEIGHT);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_DEBOUNCE_COUNT:
		switch (chan->type) {
		case IIO_STEPS:
			*val = mma9553_get_bits(data->conf.filter,
						MMA9553_MASK_CONF_FILTSTEP);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_DEBOUNCE_TIME:
		switch (chan->type) {
		case IIO_STEPS:
			*val = mma9553_get_bits(data->conf.filter,
						MMA9553_MASK_CONF_FILTTIME);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_VELOCITY:
			if (chan->channel2 != IIO_MOD_ROOT_SUM_SQUARED_X_Y_Z)
				return -EINVAL;
			*val = mma9553_get_bits(data->conf.speed_step,
						MMA9553_MASK_CONF_SPDPRD);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}