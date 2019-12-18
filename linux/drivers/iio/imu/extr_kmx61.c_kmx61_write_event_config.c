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
struct kmx61_data {int ev_enable_state; int /*<<< orphan*/  lock; scalar_t__ motion_trig_on; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  KMX61_ACC ; 
 struct kmx61_data* kmx61_get_data (struct iio_dev*) ; 
 int kmx61_set_power_state (struct kmx61_data*,int,int /*<<< orphan*/ ) ; 
 int kmx61_setup_any_motion_interrupt (struct kmx61_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmx61_write_event_config(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    int state)
{
	struct kmx61_data *data = kmx61_get_data(indio_dev);
	int ret = 0;

	if (state && data->ev_enable_state)
		return 0;

	mutex_lock(&data->lock);

	if (!state && data->motion_trig_on) {
		data->ev_enable_state = false;
		goto err_unlock;
	}

	ret = kmx61_set_power_state(data, state, KMX61_ACC);
	if (ret < 0)
		goto err_unlock;

	ret = kmx61_setup_any_motion_interrupt(data, state);
	if (ret < 0) {
		kmx61_set_power_state(data, false, KMX61_ACC);
		goto err_unlock;
	}

	data->ev_enable_state = state;

err_unlock:
	mutex_unlock(&data->lock);

	return ret;
}