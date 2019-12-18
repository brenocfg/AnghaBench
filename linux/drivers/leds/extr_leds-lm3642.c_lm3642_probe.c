#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lm3642_platform_data {int /*<<< orphan*/  strobe_pin; int /*<<< orphan*/  torch_pin; int /*<<< orphan*/  tx_pin; } ;
struct TYPE_3__ {char* name; int max_brightness; char* default_trigger; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  groups; } ;
struct lm3642_chip_data {TYPE_1__ cdev_flash; TYPE_1__ cdev_torch; int /*<<< orphan*/ * dev; TYPE_1__ cdev_indicator; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  strobe_pin; int /*<<< orphan*/  torch_pin; int /*<<< orphan*/  tx_pin; struct lm3642_platform_data* pdata; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm3642_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct lm3642_chip_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3642_chip_data*) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int lm3642_chip_init (struct lm3642_chip_data*) ; 
 int /*<<< orphan*/  lm3642_flash_groups ; 
 int /*<<< orphan*/  lm3642_indicator_brightness_set ; 
 int /*<<< orphan*/  lm3642_regmap ; 
 int /*<<< orphan*/  lm3642_strobe_brightness_set ; 
 int /*<<< orphan*/  lm3642_torch_brightness_set ; 
 int /*<<< orphan*/  lm3642_torch_groups ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3642_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct lm3642_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lm3642_chip_data *chip;

	int err;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "i2c functionality check fail.\n");
		return -EOPNOTSUPP;
	}

	if (pdata == NULL) {
		dev_err(&client->dev, "needs Platform Data.\n");
		return -ENODATA;
	}

	chip = devm_kzalloc(&client->dev,
			    sizeof(struct lm3642_chip_data), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->dev = &client->dev;
	chip->pdata = pdata;

	chip->tx_pin = pdata->tx_pin;
	chip->torch_pin = pdata->torch_pin;
	chip->strobe_pin = pdata->strobe_pin;

	chip->regmap = devm_regmap_init_i2c(client, &lm3642_regmap);
	if (IS_ERR(chip->regmap)) {
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			err);
		return err;
	}

	mutex_init(&chip->lock);
	i2c_set_clientdata(client, chip);

	err = lm3642_chip_init(chip);
	if (err < 0)
		goto err_out;

	/* flash */
	chip->cdev_flash.name = "flash";
	chip->cdev_flash.max_brightness = 16;
	chip->cdev_flash.brightness_set_blocking = lm3642_strobe_brightness_set;
	chip->cdev_flash.default_trigger = "flash";
	chip->cdev_flash.groups = lm3642_flash_groups,
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_flash);
	if (err < 0) {
		dev_err(chip->dev, "failed to register flash\n");
		goto err_out;
	}

	/* torch */
	chip->cdev_torch.name = "torch";
	chip->cdev_torch.max_brightness = 8;
	chip->cdev_torch.brightness_set_blocking = lm3642_torch_brightness_set;
	chip->cdev_torch.default_trigger = "torch";
	chip->cdev_torch.groups = lm3642_torch_groups,
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_torch);
	if (err < 0) {
		dev_err(chip->dev, "failed to register torch\n");
		goto err_create_torch_file;
	}

	/* indicator */
	chip->cdev_indicator.name = "indicator";
	chip->cdev_indicator.max_brightness = 8;
	chip->cdev_indicator.brightness_set_blocking =
						lm3642_indicator_brightness_set;
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_indicator);
	if (err < 0) {
		dev_err(chip->dev, "failed to register indicator\n");
		goto err_create_indicator_file;
	}

	dev_info(&client->dev, "LM3642 is initialized\n");
	return 0;

err_create_indicator_file:
	led_classdev_unregister(&chip->cdev_torch);
err_create_torch_file:
	led_classdev_unregister(&chip->cdev_flash);
err_out:
	return err;
}