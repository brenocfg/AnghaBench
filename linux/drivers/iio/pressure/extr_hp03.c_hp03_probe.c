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
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; struct device dev; } ;
struct hp03_priv {int /*<<< orphan*/  eeprom_client; int /*<<< orphan*/  eeprom_regmap; int /*<<< orphan*/  xclr_gpio; int /*<<< orphan*/  lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  HP03_EEPROM_ADDR ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_index (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  hp03_channels ; 
 int /*<<< orphan*/  hp03_info ; 
 int /*<<< orphan*/  hp03_regmap_config ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct hp03_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_init_i2c (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp03_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct iio_dev *indio_dev;
	struct hp03_priv *priv;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->client = client;
	mutex_init(&priv->lock);

	indio_dev->dev.parent = dev;
	indio_dev->name = id->name;
	indio_dev->channels = hp03_channels;
	indio_dev->num_channels = ARRAY_SIZE(hp03_channels);
	indio_dev->info = &hp03_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	priv->xclr_gpio = devm_gpiod_get_index(dev, "xclr", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(priv->xclr_gpio)) {
		dev_err(dev, "Failed to claim XCLR GPIO\n");
		ret = PTR_ERR(priv->xclr_gpio);
		return ret;
	}

	/*
	 * Allocate another device for the on-sensor EEPROM,
	 * which has it's dedicated I2C address and contains
	 * the calibration constants for the sensor.
	 */
	priv->eeprom_client = i2c_new_dummy_device(client->adapter, HP03_EEPROM_ADDR);
	if (IS_ERR(priv->eeprom_client)) {
		dev_err(dev, "New EEPROM I2C device failed\n");
		return PTR_ERR(priv->eeprom_client);
	}

	priv->eeprom_regmap = regmap_init_i2c(priv->eeprom_client,
					      &hp03_regmap_config);
	if (IS_ERR(priv->eeprom_regmap)) {
		dev_err(dev, "Failed to allocate EEPROM regmap\n");
		ret = PTR_ERR(priv->eeprom_regmap);
		goto err_cleanup_eeprom_client;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "Failed to register IIO device\n");
		goto err_cleanup_eeprom_regmap;
	}

	i2c_set_clientdata(client, indio_dev);

	return 0;

err_cleanup_eeprom_regmap:
	regmap_exit(priv->eeprom_regmap);

err_cleanup_eeprom_client:
	i2c_unregister_device(priv->eeprom_client);
	return ret;
}