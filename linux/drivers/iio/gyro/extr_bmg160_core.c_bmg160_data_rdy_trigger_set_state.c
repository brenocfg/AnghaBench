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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct bmg160_data {int motion_trigger_on; int dready_trigger_on; int /*<<< orphan*/  mutex; struct iio_trigger* motion_trig; scalar_t__ ev_enable_state; } ;

/* Variables and functions */
 int bmg160_set_power_state (struct bmg160_data*,int) ; 
 int bmg160_setup_any_motion_interrupt (struct bmg160_data*,int) ; 
 int bmg160_setup_new_data_interrupt (struct bmg160_data*,int) ; 
 struct bmg160_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmg160_data_rdy_trigger_set_state(struct iio_trigger *trig,
					     bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmg160_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->mutex);

	if (!state && data->ev_enable_state && data->motion_trigger_on) {
		data->motion_trigger_on = false;
		mutex_unlock(&data->mutex);
		return 0;
	}

	/*
	 * Refer to comment in bmg160_write_event_config for
	 * enable/disable operation order
	 */
	ret = bmg160_set_power_state(data, state);
	if (ret < 0) {
		mutex_unlock(&data->mutex);
		return ret;
	}
	if (data->motion_trig == trig)
		ret =  bmg160_setup_any_motion_interrupt(data, state);
	else
		ret = bmg160_setup_new_data_interrupt(data, state);
	if (ret < 0) {
		bmg160_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	}
	if (data->motion_trig == trig)
		data->motion_trigger_on = state;
	else
		data->dready_trigger_on = state;

	mutex_unlock(&data->mutex);

	return 0;
}