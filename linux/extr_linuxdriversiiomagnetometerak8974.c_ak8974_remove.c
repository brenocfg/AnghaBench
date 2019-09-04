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
struct ak8974 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_PWR_OFF ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ak8974_set_power (struct ak8974*,int /*<<< orphan*/ ) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ak8974* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak8974_remove(struct i2c_client *i2c)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(i2c);
	struct ak8974 *ak8974 = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	pm_runtime_get_sync(&i2c->dev);
	pm_runtime_put_noidle(&i2c->dev);
	pm_runtime_disable(&i2c->dev);
	ak8974_set_power(ak8974, AK8974_PWR_OFF);
	regulator_bulk_disable(ARRAY_SIZE(ak8974->regs), ak8974->regs);

	return 0;
}