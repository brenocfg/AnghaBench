#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct bma180_data {int /*<<< orphan*/  mutex; TYPE_1__* part_info; scalar_t__ trig; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_disable ) (struct bma180_data*) ;} ;

/* Variables and functions */
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct bma180_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (scalar_t__) ; 
 int /*<<< orphan*/  iio_trigger_unregister (scalar_t__) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bma180_data*) ; 

__attribute__((used)) static int bma180_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct bma180_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	if (data->trig) {
		iio_trigger_unregister(data->trig);
		iio_trigger_free(data->trig);
	}

	mutex_lock(&data->mutex);
	data->part_info->chip_disable(data);
	mutex_unlock(&data->mutex);

	return 0;
}