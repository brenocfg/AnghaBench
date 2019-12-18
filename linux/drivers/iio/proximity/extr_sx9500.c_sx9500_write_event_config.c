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
struct sx9500_data {int* event_enabled; int /*<<< orphan*/  mutex; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; size_t channel; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EV_DIR_EITHER ; 
 int IIO_EV_TYPE_THRESH ; 
 scalar_t__ IIO_PROXIMITY ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sx9500_dec_chan_users (struct sx9500_data*,size_t) ; 
 int sx9500_dec_close_far_users (struct sx9500_data*) ; 
 int sx9500_inc_chan_users (struct sx9500_data*,size_t) ; 
 int sx9500_inc_close_far_users (struct sx9500_data*) ; 

__attribute__((used)) static int sx9500_write_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     int state)
{
	struct sx9500_data *data = iio_priv(indio_dev);
	int ret;

	if (chan->type != IIO_PROXIMITY || type != IIO_EV_TYPE_THRESH ||
	    dir != IIO_EV_DIR_EITHER)
		return -EINVAL;

	mutex_lock(&data->mutex);

	if (state == 1) {
		ret = sx9500_inc_chan_users(data, chan->channel);
		if (ret < 0)
			goto out_unlock;
		ret = sx9500_inc_close_far_users(data);
		if (ret < 0)
			goto out_undo_chan;
	} else {
		ret = sx9500_dec_chan_users(data, chan->channel);
		if (ret < 0)
			goto out_unlock;
		ret = sx9500_dec_close_far_users(data);
		if (ret < 0)
			goto out_undo_chan;
	}

	data->event_enabled[chan->channel] = state;
	goto out_unlock;

out_undo_chan:
	if (state == 1)
		sx9500_dec_chan_users(data, chan->channel);
	else
		sx9500_inc_chan_users(data, chan->channel);
out_unlock:
	mutex_unlock(&data->mutex);
	return ret;
}