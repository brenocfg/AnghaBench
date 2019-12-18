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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak8975_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOWN ; 
 int /*<<< orphan*/  ak8975_power_off (struct ak8975_data*) ; 
 int /*<<< orphan*/  ak8975_set_mode (struct ak8975_data*,int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ak8975_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak8975_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct ak8975_data *data = iio_priv(indio_dev);

	pm_runtime_get_sync(&client->dev);
	pm_runtime_put_noidle(&client->dev);
	pm_runtime_disable(&client->dev);
	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	ak8975_set_mode(data, POWER_DOWN);
	ak8975_power_off(data);

	return 0;
}