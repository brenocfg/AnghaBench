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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct bh1780_data {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BH1780_PON ; 
 int /*<<< orphan*/  BH1780_PON_DELAY ; 
 int /*<<< orphan*/  BH1780_REG_CONTROL ; 
 int /*<<< orphan*/  BH1780_REG_PARTID ; 
 int BH1780_REVMASK ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  bh1780_channels ; 
 int /*<<< orphan*/  bh1780_info ; 
 int bh1780_read (struct bh1780_data*,int /*<<< orphan*/ ) ; 
 int bh1780_write (struct bh1780_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct bh1780_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1780_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct bh1780_data *bh1780;
	struct i2c_adapter *adapter = client->adapter;
	struct iio_dev *indio_dev;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		return -EIO;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*bh1780));
	if (!indio_dev)
		return -ENOMEM;

	bh1780 = iio_priv(indio_dev);
	bh1780->client = client;
	i2c_set_clientdata(client, indio_dev);

	/* Power up the device */
	ret = bh1780_write(bh1780, BH1780_REG_CONTROL, BH1780_PON);
	if (ret < 0)
		return ret;
	msleep(BH1780_PON_DELAY);
	pm_runtime_get_noresume(&client->dev);
	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);

	ret = bh1780_read(bh1780, BH1780_REG_PARTID);
	if (ret < 0)
		goto out_disable_pm;
	dev_info(&client->dev,
		 "Ambient Light Sensor, Rev : %lu\n",
		 (ret & BH1780_REVMASK));

	/*
	 * As the device takes 250 ms to even come up with a fresh
	 * measurement after power-on, do not shut it down unnecessarily.
	 * Set autosuspend to a five seconds.
	 */
	pm_runtime_set_autosuspend_delay(&client->dev, 5000);
	pm_runtime_use_autosuspend(&client->dev);
	pm_runtime_put(&client->dev);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &bh1780_info;
	indio_dev->name = "bh1780";
	indio_dev->channels = bh1780_channels;
	indio_dev->num_channels = ARRAY_SIZE(bh1780_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto out_disable_pm;
	return 0;

out_disable_pm:
	pm_runtime_put_noidle(&client->dev);
	pm_runtime_disable(&client->dev);
	return ret;
}