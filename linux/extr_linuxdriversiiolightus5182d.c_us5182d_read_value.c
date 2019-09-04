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
struct us5182d_data {scalar_t__ power_mode; int /*<<< orphan*/  lock; } ;
struct iio_chan_spec {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ IIO_LIGHT ; 
 scalar_t__ US5182D_ONESHOT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int us5182d_get_als (struct us5182d_data*) ; 
 int us5182d_get_px (struct us5182d_data*) ; 
 int us5182d_oneshot_en (struct us5182d_data*) ; 
 int us5182d_set_power_state (struct us5182d_data*,int) ; 

__attribute__((used)) static int us5182d_read_value(struct us5182d_data *data,
			      struct iio_chan_spec const *chan)
{
	int ret, value;

	mutex_lock(&data->lock);

	if (data->power_mode == US5182D_ONESHOT) {
		ret = us5182d_oneshot_en(data);
		if (ret < 0)
			goto out_err;
	}

	ret = us5182d_set_power_state(data, true);
	if (ret < 0)
		goto out_err;

	if (chan->type == IIO_LIGHT)
		ret = us5182d_get_als(data);
	else
		ret = us5182d_get_px(data);
	if (ret < 0)
		goto out_poweroff;

	value = ret;

	ret = us5182d_set_power_state(data, false);
	if (ret < 0)
		goto out_err;

	mutex_unlock(&data->lock);
	return value;

out_poweroff:
	us5182d_set_power_state(data, false);
out_err:
	mutex_unlock(&data->lock);
	return ret;
}