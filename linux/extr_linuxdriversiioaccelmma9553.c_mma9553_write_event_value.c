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
struct TYPE_2__ {int /*<<< orphan*/  actthd; int /*<<< orphan*/  speed_step; } ;
struct mma9553_data {int /*<<< orphan*/  mutex; TYPE_1__ conf; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACTIVITY 131 
#define  IIO_EV_INFO_PERIOD 130 
#define  IIO_EV_INFO_VALUE 129 
#define  IIO_STEPS 128 
 int MMA9553_ACTIVITY_SEC_TO_THD (int) ; 
 int MMA9553_ACTIVITY_THD_TO_SEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_STEPCOALESCE ; 
 int /*<<< orphan*/  MMA9553_MASK_CONF_WORD ; 
 int /*<<< orphan*/  MMA9553_MAX_ACTTHD ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_ACTTHD ; 
 int /*<<< orphan*/  MMA9553_REG_CONF_SPEED_STEP ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9553_set_config (struct mma9553_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_write_event_value(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     enum iio_event_info info,
				     int val, int val2)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	int ret;

	switch (info) {
	case IIO_EV_INFO_VALUE:
		switch (chan->type) {
		case IIO_STEPS:
			if (val < 0 || val > 255)
				return -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data,
						MMA9553_REG_CONF_SPEED_STEP,
						&data->conf.speed_step, val,
						MMA9553_MASK_CONF_STEPCOALESCE);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	case IIO_EV_INFO_PERIOD:
		switch (chan->type) {
		case IIO_ACTIVITY:
			if (val < 0 || val > MMA9553_ACTIVITY_THD_TO_SEC(
			    MMA9553_MAX_ACTTHD))
				return -EINVAL;
			mutex_lock(&data->mutex);
			ret = mma9553_set_config(data, MMA9553_REG_CONF_ACTTHD,
						 &data->conf.actthd,
						 MMA9553_ACTIVITY_SEC_TO_THD
						 (val), MMA9553_MASK_CONF_WORD);
			mutex_unlock(&data->mutex);
			return ret;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}