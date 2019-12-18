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
struct regmap {int dummy; } ;
struct mlx90632_data {int emissivity; struct regmap* regmap; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 unsigned int MLX90632_DSP_MASK ; 
 unsigned int MLX90632_DSP_VERSION ; 
 int /*<<< orphan*/  MLX90632_EE_VERSION ; 
 unsigned int MLX90632_ID_CONSUMER ; 
 unsigned int MLX90632_ID_MEDICAL ; 
 int /*<<< orphan*/  MLX90632_SLEEP_DELAY_MS ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mlx90632_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mlx90632_channels ; 
 int /*<<< orphan*/  mlx90632_info ; 
 int /*<<< orphan*/  mlx90632_regmap ; 
 int /*<<< orphan*/  mlx90632_sleep (struct mlx90632_data*) ; 
 int mlx90632_wakeup (struct mlx90632_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mlx90632_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct mlx90632_data *mlx90632;
	struct regmap *regmap;
	int ret;
	unsigned int read;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*mlx90632));
	if (!indio_dev) {
		dev_err(&client->dev, "Failed to allocate device\n");
		return -ENOMEM;
	}

	regmap = devm_regmap_init_i2c(client, &mlx90632_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	mlx90632 = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	mlx90632->client = client;
	mlx90632->regmap = regmap;

	mutex_init(&mlx90632->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mlx90632_info;
	indio_dev->channels = mlx90632_channels;
	indio_dev->num_channels = ARRAY_SIZE(mlx90632_channels);

	ret = mlx90632_wakeup(mlx90632);
	if (ret < 0) {
		dev_err(&client->dev, "Wakeup failed: %d\n", ret);
		return ret;
	}

	ret = regmap_read(mlx90632->regmap, MLX90632_EE_VERSION, &read);
	if (ret < 0) {
		dev_err(&client->dev, "read of version failed: %d\n", ret);
		return ret;
	}
	if (read == MLX90632_ID_MEDICAL) {
		dev_dbg(&client->dev,
			"Detected Medical EEPROM calibration %x\n", read);
	} else if (read == MLX90632_ID_CONSUMER) {
		dev_dbg(&client->dev,
			"Detected Consumer EEPROM calibration %x\n", read);
	} else if ((read & MLX90632_DSP_MASK) == MLX90632_DSP_VERSION) {
		dev_dbg(&client->dev,
			"Detected Unknown EEPROM calibration %x\n", read);	
	} else {
		dev_err(&client->dev,
			"Wrong DSP version %x (expected %x)\n",
			read, MLX90632_DSP_VERSION);
		return -EPROTONOSUPPORT;
	}

	mlx90632->emissivity = 1000;

	pm_runtime_disable(&client->dev);
	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0) {
		mlx90632_sleep(mlx90632);
		return ret;
	}
	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, MLX90632_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	return iio_device_register(indio_dev);
}