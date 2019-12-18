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
struct max44009_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_INT_TIME ; 
 scalar_t__ IIO_LIGHT ; 
 struct max44009_data* iio_priv (struct iio_dev*) ; 
 int max44009_write_int_time (struct max44009_data*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max44009_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan, int val,
			      int val2, long mask)
{
	struct max44009_data *data = iio_priv(indio_dev);
	int ret;

	if (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_LIGHT) {
		mutex_lock(&data->lock);
		ret = max44009_write_int_time(data, val, val2);
		mutex_unlock(&data->lock);
		return ret;
	}
	return -EINVAL;
}