#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lm3646_platform_data {int /*<<< orphan*/  led1_flash_brt; int /*<<< orphan*/  led1_torch_brt; int /*<<< orphan*/  flash_timeout; } ;
struct lm3646_flash {int /*<<< orphan*/ * dev; struct lm3646_platform_data* pdata; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM3646_FLASH_TOUT_MAX ; 
 int /*<<< orphan*/  LM3646_LED1_FLASH_BRT_MAX ; 
 int /*<<< orphan*/  LM3646_LED1_TORCH_BRT_MAX ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct lm3646_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3646_flash*) ; 
 int lm3646_init_device (struct lm3646_flash*) ; 
 int /*<<< orphan*/  lm3646_regmap ; 
 int lm3646_subdev_init (struct lm3646_flash*) ; 

__attribute__((used)) static int lm3646_probe(struct i2c_client *client,
			const struct i2c_device_id *devid)
{
	struct lm3646_flash *flash;
	struct lm3646_platform_data *pdata = dev_get_platdata(&client->dev);
	int rval;

	flash = devm_kzalloc(&client->dev, sizeof(*flash), GFP_KERNEL);
	if (flash == NULL)
		return -ENOMEM;

	flash->regmap = devm_regmap_init_i2c(client, &lm3646_regmap);
	if (IS_ERR(flash->regmap))
		return PTR_ERR(flash->regmap);

	/* check device tree if there is no platform data */
	if (pdata == NULL) {
		pdata = devm_kzalloc(&client->dev,
				     sizeof(struct lm3646_platform_data),
				     GFP_KERNEL);
		if (pdata == NULL)
			return -ENOMEM;
		/* use default data in case of no platform data */
		pdata->flash_timeout = LM3646_FLASH_TOUT_MAX;
		pdata->led1_torch_brt = LM3646_LED1_TORCH_BRT_MAX;
		pdata->led1_flash_brt = LM3646_LED1_FLASH_BRT_MAX;
	}
	flash->pdata = pdata;
	flash->dev = &client->dev;

	rval = lm3646_subdev_init(flash);
	if (rval < 0)
		return rval;

	rval = lm3646_init_device(flash);
	if (rval < 0)
		return rval;

	i2c_set_clientdata(client, flash);

	return 0;
}