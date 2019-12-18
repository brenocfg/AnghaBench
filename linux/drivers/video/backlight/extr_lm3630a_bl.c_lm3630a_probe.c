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
struct lm3630a_platform_data {scalar_t__ pwm_ctrl; void* ledb_init_brt; void* leda_init_brt; void* ledb_max_brt; void* leda_max_brt; } ;
struct lm3630a_chip {scalar_t__ irq; int /*<<< orphan*/  pwmd; int /*<<< orphan*/ * dev; struct lm3630a_platform_data* pdata; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 void* LM3630A_MAX_BRIGHTNESS ; 
 scalar_t__ LM3630A_PWM_DISABLE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lm3630a_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pwm_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm3630a_chip*) ; 
 int lm3630a_backlight_register (struct lm3630a_chip*) ; 
 int lm3630a_chip_init (struct lm3630a_chip*) ; 
 int lm3630a_intr_config (struct lm3630a_chip*) ; 
 int lm3630a_parse_node (struct lm3630a_chip*,struct lm3630a_platform_data*) ; 
 int /*<<< orphan*/  lm3630a_regmap ; 
 int /*<<< orphan*/  pwm_apply_args (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3630a_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct lm3630a_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lm3630a_chip *pchip;
	int rval;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "fail : i2c functionality check\n");
		return -EOPNOTSUPP;
	}

	pchip = devm_kzalloc(&client->dev, sizeof(struct lm3630a_chip),
			     GFP_KERNEL);
	if (!pchip)
		return -ENOMEM;
	pchip->dev = &client->dev;

	pchip->regmap = devm_regmap_init_i2c(client, &lm3630a_regmap);
	if (IS_ERR(pchip->regmap)) {
		rval = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail : allocate reg. map: %d\n", rval);
		return rval;
	}

	i2c_set_clientdata(client, pchip);
	if (pdata == NULL) {
		pdata = devm_kzalloc(pchip->dev,
				     sizeof(struct lm3630a_platform_data),
				     GFP_KERNEL);
		if (pdata == NULL)
			return -ENOMEM;

		/* default values */
		pdata->leda_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->leda_init_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_init_brt = LM3630A_MAX_BRIGHTNESS;

		rval = lm3630a_parse_node(pchip, pdata);
		if (rval) {
			dev_err(&client->dev, "fail : parse node\n");
			return rval;
		}
	}
	pchip->pdata = pdata;

	/* chip initialize */
	rval = lm3630a_chip_init(pchip);
	if (rval < 0) {
		dev_err(&client->dev, "fail : init chip\n");
		return rval;
	}
	/* backlight register */
	rval = lm3630a_backlight_register(pchip);
	if (rval < 0) {
		dev_err(&client->dev, "fail : backlight register.\n");
		return rval;
	}
	/* pwm */
	if (pdata->pwm_ctrl != LM3630A_PWM_DISABLE) {
		pchip->pwmd = devm_pwm_get(pchip->dev, "lm3630a-pwm");
		if (IS_ERR(pchip->pwmd)) {
			dev_err(&client->dev, "fail : get pwm device\n");
			return PTR_ERR(pchip->pwmd);
		}

		/*
		 * FIXME: pwm_apply_args() should be removed when switching to
		 * the atomic PWM API.
		 */
		pwm_apply_args(pchip->pwmd);
	}

	/* interrupt enable  : irq 0 is not allowed */
	pchip->irq = client->irq;
	if (pchip->irq) {
		rval = lm3630a_intr_config(pchip);
		if (rval < 0)
			return rval;
	}
	dev_info(&client->dev, "LM3630A backlight register OK.\n");
	return 0;
}