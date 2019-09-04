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
struct apds9960_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apds9960_set_powermode (struct apds9960_data*,int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct apds9960_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds9960_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct apds9960_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);
	apds9960_set_powermode(data, 0);

	return 0;
}