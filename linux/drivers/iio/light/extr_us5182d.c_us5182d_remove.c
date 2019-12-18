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
struct us5182d_data {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  US5182D_CFG0_SHUTDOWN_EN ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int us5182d_shutdown_en (struct us5182d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int us5182d_remove(struct i2c_client *client)
{
	struct us5182d_data *data = iio_priv(i2c_get_clientdata(client));

	iio_device_unregister(i2c_get_clientdata(client));

	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);

	return us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
}