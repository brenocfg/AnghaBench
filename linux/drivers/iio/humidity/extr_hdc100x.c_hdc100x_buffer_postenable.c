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
struct hdc100x_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDC100X_REG_CONFIG_ACQ_MODE ; 
 int hdc100x_update_config (struct hdc100x_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdc100x_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdc100x_buffer_postenable(struct iio_dev *indio_dev)
{
	struct hdc100x_data *data = iio_priv(indio_dev);
	int ret;

	/* Buffer is enabled. First set ACQ Mode, then attach poll func */
	mutex_lock(&data->lock);
	ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_ACQ_MODE,
				    HDC100X_REG_CONFIG_ACQ_MODE);
	mutex_unlock(&data->lock);
	if (ret)
		return ret;

	return iio_triggered_buffer_postenable(indio_dev);
}