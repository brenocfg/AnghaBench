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
struct mma9553_event {int enabled; } ;
struct mma9553_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int mma9551_set_power_state (int /*<<< orphan*/ ,int) ; 
 int mma9553_conf_gpio (struct mma9553_data*) ; 
 struct mma9553_event* mma9553_get_event (struct mma9553_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_write_event_config(struct iio_dev *indio_dev,
				      const struct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_direction dir, int state)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	struct mma9553_event *event;
	int ret;

	event = mma9553_get_event(data, chan->type, chan->channel2, dir);
	if (!event)
		return -EINVAL;

	if (event->enabled == state)
		return 0;

	mutex_lock(&data->mutex);

	ret = mma9551_set_power_state(data->client, state);
	if (ret < 0)
		goto err_out;
	event->enabled = state;

	ret = mma9553_conf_gpio(data);
	if (ret < 0)
		goto err_conf_gpio;

	mutex_unlock(&data->mutex);

	return 0;

err_conf_gpio:
	if (state) {
		event->enabled = false;
		mma9551_set_power_state(data->client, false);
	}
err_out:
	mutex_unlock(&data->mutex);
	return ret;
}