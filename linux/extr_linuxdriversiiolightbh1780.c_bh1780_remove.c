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
struct bh1780_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1780_POFF ; 
 int /*<<< orphan*/  BH1780_REG_CONTROL ; 
 int bh1780_write (struct bh1780_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct bh1780_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1780_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct bh1780_data *bh1780 = iio_priv(indio_dev);
	int ret;

	iio_device_unregister(indio_dev);
	pm_runtime_get_sync(&client->dev);
	pm_runtime_put_noidle(&client->dev);
	pm_runtime_disable(&client->dev);
	ret = bh1780_write(bh1780, BH1780_REG_CONTROL, BH1780_POFF);
	if (ret < 0) {
		dev_err(&client->dev, "failed to power off\n");
		return ret;
	}

	return 0;
}