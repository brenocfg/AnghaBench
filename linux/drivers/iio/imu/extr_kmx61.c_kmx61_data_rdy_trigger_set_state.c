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
typedef  int /*<<< orphan*/  u8 ;
struct kmx61_data {int motion_trig_on; int acc_dready_trig_on; int mag_dready_trig_on; int /*<<< orphan*/  lock; struct iio_trigger* mag_dready_trig; struct iio_trigger* acc_dready_trig; struct iio_trigger* motion_trig; scalar_t__ ev_enable_state; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KMX61_ACC ; 
 int /*<<< orphan*/  KMX61_MAG ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 struct kmx61_data* kmx61_get_data (struct iio_dev*) ; 
 int kmx61_set_power_state (struct kmx61_data*,int,int /*<<< orphan*/ ) ; 
 int kmx61_setup_any_motion_interrupt (struct kmx61_data*,int) ; 
 int kmx61_setup_new_data_interrupt (struct kmx61_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmx61_data_rdy_trigger_set_state(struct iio_trigger *trig,
					    bool state)
{
	int ret = 0;
	u8 device;

	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct kmx61_data *data = kmx61_get_data(indio_dev);

	mutex_lock(&data->lock);

	if (!state && data->ev_enable_state && data->motion_trig_on) {
		data->motion_trig_on = false;
		goto err_unlock;
	}

	if (data->acc_dready_trig == trig || data->motion_trig == trig)
		device = KMX61_ACC;
	else
		device = KMX61_MAG;

	ret = kmx61_set_power_state(data, state, device);
	if (ret < 0)
		goto err_unlock;

	if (data->acc_dready_trig == trig || data->mag_dready_trig == trig)
		ret = kmx61_setup_new_data_interrupt(data, state, device);
	else
		ret = kmx61_setup_any_motion_interrupt(data, state);
	if (ret < 0) {
		kmx61_set_power_state(data, false, device);
		goto err_unlock;
	}

	if (data->acc_dready_trig == trig)
		data->acc_dready_trig_on = state;
	else if (data->mag_dready_trig == trig)
		data->mag_dready_trig_on = state;
	else
		data->motion_trig_on = state;
err_unlock:
	mutex_unlock(&data->lock);

	return ret;
}