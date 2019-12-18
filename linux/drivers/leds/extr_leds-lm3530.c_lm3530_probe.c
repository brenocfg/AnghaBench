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
struct lm3530_platform_data {scalar_t__ mode; scalar_t__ brt_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct lm3530_data {scalar_t__ mode; int enable; TYPE_1__ led_dev; struct lm3530_platform_data* pdata; int /*<<< orphan*/ * regulator; int /*<<< orphan*/  brightness; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ LM3530_BL_MODE_PWM ; 
 int /*<<< orphan*/  LM3530_LED_DEV ; 
 int /*<<< orphan*/  MAX_BRIGHTNESS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm3530_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct lm3530_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3530_data*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lm3530_brightness_set ; 
 int /*<<< orphan*/  lm3530_groups ; 
 int lm3530_init_registers (struct lm3530_data*) ; 

__attribute__((used)) static int lm3530_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct lm3530_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lm3530_data *drvdata;
	int err = 0;

	if (pdata == NULL) {
		dev_err(&client->dev, "platform data required\n");
		return -ENODEV;
	}

	/* BL mode */
	if (pdata->mode > LM3530_BL_MODE_PWM) {
		dev_err(&client->dev, "Illegal Mode request\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C_FUNC_I2C not supported\n");
		return -EIO;
	}

	drvdata = devm_kzalloc(&client->dev, sizeof(struct lm3530_data),
				GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	drvdata->mode = pdata->mode;
	drvdata->client = client;
	drvdata->pdata = pdata;
	drvdata->brightness = LED_OFF;
	drvdata->enable = false;
	drvdata->led_dev.name = LM3530_LED_DEV;
	drvdata->led_dev.brightness_set = lm3530_brightness_set;
	drvdata->led_dev.max_brightness = MAX_BRIGHTNESS;
	drvdata->led_dev.groups = lm3530_groups;

	i2c_set_clientdata(client, drvdata);

	drvdata->regulator = devm_regulator_get(&client->dev, "vin");
	if (IS_ERR(drvdata->regulator)) {
		dev_err(&client->dev, "regulator get failed\n");
		err = PTR_ERR(drvdata->regulator);
		drvdata->regulator = NULL;
		return err;
	}

	if (drvdata->pdata->brt_val) {
		err = lm3530_init_registers(drvdata);
		if (err < 0) {
			dev_err(&client->dev,
				"Register Init failed: %d\n", err);
			return err;
		}
	}
	err = led_classdev_register(&client->dev, &drvdata->led_dev);
	if (err < 0) {
		dev_err(&client->dev, "Register led class failed: %d\n", err);
		return err;
	}

	return 0;
}