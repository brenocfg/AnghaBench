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
struct iio_chan_spec {int dummy; } ;
struct bmg160_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int bmg160_set_bw (struct bmg160_data*,int) ; 
 int bmg160_set_filter (struct bmg160_data*,int) ; 
 int bmg160_set_power_state (struct bmg160_data*,int) ; 
 int bmg160_set_scale (struct bmg160_data*,int) ; 
 struct bmg160_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmg160_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct bmg160_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		/*
		 * Section 4.2 of spec
		 * In suspend mode, the only supported operations are reading
		 * registers as well as writing to the (0x14) softreset
		 * register. Since we will be in suspend mode by default, change
		 * mode to power on for other writes.
		 */
		ret = bmg160_set_power_state(data, true);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_bw(data, val);
		if (ret < 0) {
			bmg160_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		if (val2)
			return -EINVAL;

		mutex_lock(&data->mutex);
		ret = bmg160_set_power_state(data, true);
		if (ret < 0) {
			bmg160_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_filter(data, val);
		if (ret < 0) {
			bmg160_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	case IIO_CHAN_INFO_SCALE:
		if (val)
			return -EINVAL;

		mutex_lock(&data->mutex);
		/* Refer to comments above for the suspend mode ops */
		ret = bmg160_set_power_state(data, true);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_scale(data, val2);
		if (ret < 0) {
			bmg160_set_power_state(data, false);
			mutex_unlock(&data->mutex);
			return ret;
		}
		ret = bmg160_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}