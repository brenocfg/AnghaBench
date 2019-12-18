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
struct lm355x_platform_data {int dummy; } ;
struct TYPE_3__ {char* name; int max_brightness; char* default_trigger; int /*<<< orphan*/  groups; int /*<<< orphan*/  brightness_set_blocking; } ;
struct lm355x_chip_data {int type; TYPE_1__ cdev_flash; TYPE_1__ cdev_torch; TYPE_1__ cdev_indicator; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; struct lm355x_platform_data* pdata; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; } ;
struct i2c_device_id {int driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  CHIP_LM3554 129 
#define  CHIP_LM3556 128 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm355x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct lm355x_chip_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm355x_chip_data*) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  lm3554_regs ; 
 int /*<<< orphan*/  lm3556_regs ; 
 int lm355x_chip_init (struct lm355x_chip_data*) ; 
 int /*<<< orphan*/  lm355x_indicator_brightness_set ; 
 int /*<<< orphan*/  lm355x_indicator_groups ; 
 int /*<<< orphan*/ * lm355x_name ; 
 int /*<<< orphan*/  lm355x_regmap ; 
 int /*<<< orphan*/  lm355x_strobe_brightness_set ; 
 int /*<<< orphan*/  lm355x_torch_brightness_set ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm355x_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct lm355x_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lm355x_chip_data *chip;

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
			    sizeof(struct lm355x_chip_data), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->dev = &client->dev;
	chip->type = id->driver_data;
	switch (id->driver_data) {
	case CHIP_LM3554:
		chip->regs = lm3554_regs;
		break;
	case CHIP_LM3556:
		chip->regs = lm3556_regs;
		break;
	default:
		return -ENOSYS;
	}
	chip->pdata = pdata;

	chip->regmap = devm_regmap_init_i2c(client, &lm355x_regmap);
	if (IS_ERR(chip->regmap)) {
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n", err);
		return err;
	}

	mutex_init(&chip->lock);
	i2c_set_clientdata(client, chip);

	err = lm355x_chip_init(chip);
	if (err < 0)
		goto err_out;

	/* flash */
	chip->cdev_flash.name = "flash";
	chip->cdev_flash.max_brightness = 16;
	chip->cdev_flash.brightness_set_blocking = lm355x_strobe_brightness_set;
	chip->cdev_flash.default_trigger = "flash";
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_flash);
	if (err < 0)
		goto err_out;
	/* torch */
	chip->cdev_torch.name = "torch";
	chip->cdev_torch.max_brightness = 8;
	chip->cdev_torch.brightness_set_blocking = lm355x_torch_brightness_set;
	chip->cdev_torch.default_trigger = "torch";
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_torch);
	if (err < 0)
		goto err_create_torch_file;
	/* indicator */
	chip->cdev_indicator.name = "indicator";
	if (id->driver_data == CHIP_LM3554)
		chip->cdev_indicator.max_brightness = 4;
	else
		chip->cdev_indicator.max_brightness = 8;
	chip->cdev_indicator.brightness_set_blocking =
					lm355x_indicator_brightness_set;
	/* indicator pattern control only for LM3556 */
	if (id->driver_data == CHIP_LM3556)
		chip->cdev_indicator.groups = lm355x_indicator_groups;
	err = led_classdev_register((struct device *)
				    &client->dev, &chip->cdev_indicator);
	if (err < 0)
		goto err_create_indicator_file;

	dev_info(&client->dev, "%s is initialized\n",
		 lm355x_name[id->driver_data]);
	return 0;

err_create_indicator_file:
	led_classdev_unregister(&chip->cdev_torch);
err_create_torch_file:
	led_classdev_unregister(&chip->cdev_flash);
err_out:
	return err;
}