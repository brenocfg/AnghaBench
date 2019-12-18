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
struct kmx61_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  motion_trig; int /*<<< orphan*/  mag_dready_trig; int /*<<< orphan*/  acc_dready_trig; int /*<<< orphan*/  mag_indio_dev; int /*<<< orphan*/  acc_indio_dev; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KMX61_ACC ; 
 int /*<<< orphan*/  KMX61_ALL_STBY ; 
 int KMX61_MAG ; 
 struct kmx61_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmx61_set_mode (struct kmx61_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmx61_remove(struct i2c_client *client)
{
	struct kmx61_data *data = i2c_get_clientdata(client);

	iio_device_unregister(data->acc_indio_dev);
	iio_device_unregister(data->mag_indio_dev);

	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);
	pm_runtime_put_noidle(&client->dev);

	if (client->irq > 0) {
		iio_triggered_buffer_cleanup(data->acc_indio_dev);
		iio_triggered_buffer_cleanup(data->mag_indio_dev);
		iio_trigger_unregister(data->acc_dready_trig);
		iio_trigger_unregister(data->mag_dready_trig);
		iio_trigger_unregister(data->motion_trig);
	}

	mutex_lock(&data->lock);
	kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	mutex_unlock(&data->lock);

	return 0;
}