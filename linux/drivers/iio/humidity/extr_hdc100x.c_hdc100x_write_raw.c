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
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct hdc100x_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDC100X_REG_CONFIG_HEATER_EN ; 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  IIO_CURRENT ; 
 int hdc100x_set_it_time (struct hdc100x_data*,int /*<<< orphan*/ ,int) ; 
 int hdc100x_update_config (struct hdc100x_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdc100x_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdc100x_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct hdc100x_data *data = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (val != 0)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_set_it_time(data, chan->address, val2);
		mutex_unlock(&data->lock);
		return ret;
	case IIO_CHAN_INFO_RAW:
		if (chan->type != IIO_CURRENT || val2 != 0)
			return -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_HEATER_EN,
					val ? HDC100X_REG_CONFIG_HEATER_EN : 0);
		mutex_unlock(&data->lock);
		return ret;
	default:
		return -EINVAL;
	}
}