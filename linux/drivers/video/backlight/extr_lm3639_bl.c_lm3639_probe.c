#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lm3639_platform_data {int /*<<< orphan*/  max_brt_led; int /*<<< orphan*/  init_brt_led; } ;
struct TYPE_7__ {char* name; int max_brightness; int /*<<< orphan*/  brightness_set; } ;
struct lm3639_chip_data {TYPE_3__* bled; TYPE_1__ cdev_flash; TYPE_1__ cdev_torch; int /*<<< orphan*/ * dev; TYPE_3__* regmap; struct lm3639_platform_data* pdata; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct device {int dummy; } ;
struct backlight_properties {int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODATA ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_attr_bled_mode ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm3639_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct lm3639_chip_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct lm3639_chip_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3639_chip_data*) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  lm3639_bled_ops ; 
 int lm3639_chip_init (struct lm3639_chip_data*) ; 
 int /*<<< orphan*/  lm3639_flash_brightness_set ; 
 int /*<<< orphan*/  lm3639_regmap ; 
 int /*<<< orphan*/  lm3639_torch_brightness_set ; 

__attribute__((used)) static int lm3639_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	int ret;
	struct lm3639_chip_data *pchip;
	struct lm3639_platform_data *pdata = dev_get_platdata(&client->dev);
	struct backlight_properties props;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "i2c functionality check fail.\n");
		return -EOPNOTSUPP;
	}

	if (pdata == NULL) {
		dev_err(&client->dev, "Needs Platform Data.\n");
		return -ENODATA;
	}

	pchip = devm_kzalloc(&client->dev,
			     sizeof(struct lm3639_chip_data), GFP_KERNEL);
	if (!pchip)
		return -ENOMEM;

	pchip->pdata = pdata;
	pchip->dev = &client->dev;

	pchip->regmap = devm_regmap_init_i2c(client, &lm3639_regmap);
	if (IS_ERR(pchip->regmap)) {
		ret = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail : allocate register map: %d\n",
			ret);
		return ret;
	}
	i2c_set_clientdata(client, pchip);

	/* chip initialize */
	ret = lm3639_chip_init(pchip);
	if (ret < 0) {
		dev_err(&client->dev, "fail : chip init\n");
		goto err_out;
	}

	/* backlight */
	props.type = BACKLIGHT_RAW;
	props.brightness = pdata->init_brt_led;
	props.max_brightness = pdata->max_brt_led;
	pchip->bled =
	    devm_backlight_device_register(pchip->dev, "lm3639_bled",
					   pchip->dev, pchip, &lm3639_bled_ops,
					   &props);
	if (IS_ERR(pchip->bled)) {
		dev_err(&client->dev, "fail : backlight register\n");
		ret = PTR_ERR(pchip->bled);
		goto err_out;
	}

	ret = device_create_file(&(pchip->bled->dev), &dev_attr_bled_mode);
	if (ret < 0) {
		dev_err(&client->dev, "failed : add sysfs entries\n");
		goto err_out;
	}

	/* flash */
	pchip->cdev_flash.name = "lm3639_flash";
	pchip->cdev_flash.max_brightness = 16;
	pchip->cdev_flash.brightness_set = lm3639_flash_brightness_set;
	ret = led_classdev_register((struct device *)
				    &client->dev, &pchip->cdev_flash);
	if (ret < 0) {
		dev_err(&client->dev, "fail : flash register\n");
		goto err_flash;
	}

	/* torch */
	pchip->cdev_torch.name = "lm3639_torch";
	pchip->cdev_torch.max_brightness = 8;
	pchip->cdev_torch.brightness_set = lm3639_torch_brightness_set;
	ret = led_classdev_register((struct device *)
				    &client->dev, &pchip->cdev_torch);
	if (ret < 0) {
		dev_err(&client->dev, "fail : torch register\n");
		goto err_torch;
	}

	return 0;

err_torch:
	led_classdev_unregister(&pchip->cdev_flash);
err_flash:
	device_remove_file(&(pchip->bled->dev), &dev_attr_bled_mode);
err_out:
	return ret;
}