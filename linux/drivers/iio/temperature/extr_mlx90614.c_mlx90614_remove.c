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
struct mlx90614_data {scalar_t__ wakeup_gpio; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct mlx90614_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mlx90614_sleep (struct mlx90614_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx90614_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct mlx90614_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	if (data->wakeup_gpio) {
		pm_runtime_disable(&client->dev);
		if (!pm_runtime_status_suspended(&client->dev))
			mlx90614_sleep(data);
		pm_runtime_set_suspended(&client->dev);
	}

	return 0;
}