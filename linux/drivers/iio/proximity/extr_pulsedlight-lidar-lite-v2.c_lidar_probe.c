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
struct lidar_data {int i2c_enabled; struct iio_dev* indio_dev; struct i2c_client* client; int /*<<< orphan*/  xfer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  LIDAR_DRV_NAME ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct lidar_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lidar_channels ; 
 int /*<<< orphan*/  lidar_i2c_xfer ; 
 int /*<<< orphan*/  lidar_info ; 
 int /*<<< orphan*/  lidar_smbus_xfer ; 
 int /*<<< orphan*/  lidar_trigger_handler ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lidar_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct lidar_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);

	if (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		data->xfer = lidar_i2c_xfer;
		data->i2c_enabled = 1;
	} else if (i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BYTE))
		data->xfer = lidar_smbus_xfer;
	else
		return -EOPNOTSUPP;

	indio_dev->info = &lidar_info;
	indio_dev->name = LIDAR_DRV_NAME;
	indio_dev->channels = lidar_channels;
	indio_dev->num_channels = ARRAY_SIZE(lidar_channels);
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;

	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->indio_dev = indio_dev;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 lidar_trigger_handler, NULL);
	if (ret)
		return ret;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_unreg_buffer;

	pm_runtime_set_autosuspend_delay(&client->dev, 1000);
	pm_runtime_use_autosuspend(&client->dev);

	ret = pm_runtime_set_active(&client->dev);
	if (ret)
		goto error_unreg_buffer;
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

error_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

	return ret;
}