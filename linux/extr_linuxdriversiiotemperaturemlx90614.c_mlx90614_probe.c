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
struct mlx90614_data {scalar_t__ wakeup_gpio; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; void* channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MLX90614_AUTOSLEEP_DELAY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mlx90614_data* iio_priv (struct iio_dev*) ; 
 void* mlx90614_channels ; 
 int /*<<< orphan*/  mlx90614_info ; 
 int mlx90614_probe_num_ir_sensors (struct i2c_client*) ; 
 scalar_t__ mlx90614_probe_wakeup (struct i2c_client*) ; 
 int /*<<< orphan*/  mlx90614_wakeup (struct mlx90614_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx90614_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct mlx90614_data *data;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);
	data->wakeup_gpio = mlx90614_probe_wakeup(client);

	mlx90614_wakeup(data);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mlx90614_info;

	ret = mlx90614_probe_num_ir_sensors(client);
	switch (ret) {
	case 0:
		dev_dbg(&client->dev, "Found single sensor");
		indio_dev->channels = mlx90614_channels;
		indio_dev->num_channels = 2;
		break;
	case 1:
		dev_dbg(&client->dev, "Found dual sensor");
		indio_dev->channels = mlx90614_channels;
		indio_dev->num_channels = 3;
		break;
	default:
		return ret;
	}

	if (data->wakeup_gpio) {
		pm_runtime_set_autosuspend_delay(&client->dev,
						 MLX90614_AUTOSLEEP_DELAY);
		pm_runtime_use_autosuspend(&client->dev);
		pm_runtime_set_active(&client->dev);
		pm_runtime_enable(&client->dev);
	}

	return iio_device_register(indio_dev);
}