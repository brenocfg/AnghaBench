#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lp55xx_platform_data {int /*<<< orphan*/  num_channels; } ;
struct lp55xx_led {int dummy; } ;
struct lp55xx_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/ * cfg; struct lp55xx_platform_data* pdata; struct i2c_client* cl; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lp55xx_platform_data*) ; 
 int PTR_ERR (struct lp55xx_platform_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct lp55xx_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct lp55xx_led* devm_kcalloc (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct lp55xx_chip* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lp55xx_led*) ; 
 int /*<<< orphan*/  lp55xx_deinit_device (struct lp55xx_chip*) ; 
 int lp55xx_init_device (struct lp55xx_chip*) ; 
 struct lp55xx_platform_data* lp55xx_of_populate_pdata (TYPE_1__*,struct device_node*) ; 
 int lp55xx_register_leds (struct lp55xx_led*,struct lp55xx_chip*) ; 
 int lp55xx_register_sysfs (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp55xx_unregister_leds (struct lp55xx_led*,struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp8501_cfg ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8501_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct lp55xx_chip *chip;
	struct lp55xx_led *led;
	struct lp55xx_platform_data *pdata = dev_get_platdata(&client->dev);
	struct device_node *np = client->dev.of_node;

	if (!pdata) {
		if (np) {
			pdata = lp55xx_of_populate_pdata(&client->dev, np);
			if (IS_ERR(pdata))
				return PTR_ERR(pdata);
		} else {
			dev_err(&client->dev, "no platform data\n");
			return -EINVAL;
		}
	}

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	led = devm_kcalloc(&client->dev,
			pdata->num_channels, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	chip->cl = client;
	chip->pdata = pdata;
	chip->cfg = &lp8501_cfg;

	mutex_init(&chip->lock);

	i2c_set_clientdata(client, led);

	ret = lp55xx_init_device(chip);
	if (ret)
		goto err_init;

	dev_info(&client->dev, "%s Programmable led chip found\n", id->name);

	ret = lp55xx_register_leds(led, chip);
	if (ret)
		goto err_register_leds;

	ret = lp55xx_register_sysfs(chip);
	if (ret) {
		dev_err(&client->dev, "registering sysfs failed\n");
		goto err_register_sysfs;
	}

	return 0;

err_register_sysfs:
	lp55xx_unregister_leds(led, chip);
err_register_leds:
	lp55xx_deinit_device(chip);
err_init:
	return ret;
}