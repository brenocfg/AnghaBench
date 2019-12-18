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
struct rc5t583_platform_data {int /*<<< orphan*/  irq_base; } ;
struct rc5t583 {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct rc5t583_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct rc5t583* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rc5t583*) ; 
 int rc5t583_clear_ext_power_req (struct rc5t583*,struct rc5t583_platform_data*) ; 
 int rc5t583_irq_init (struct rc5t583*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc5t583_regmap_config ; 
 int /*<<< orphan*/  rc5t583_subdevs ; 

__attribute__((used)) static int rc5t583_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct rc5t583 *rc5t583;
	struct rc5t583_platform_data *pdata = dev_get_platdata(&i2c->dev);
	int ret;

	if (!pdata) {
		dev_err(&i2c->dev, "Err: Platform data not found\n");
		return -EINVAL;
	}

	rc5t583 = devm_kzalloc(&i2c->dev, sizeof(*rc5t583), GFP_KERNEL);
	if (!rc5t583)
		return -ENOMEM;

	rc5t583->dev = &i2c->dev;
	i2c_set_clientdata(i2c, rc5t583);

	rc5t583->regmap = devm_regmap_init_i2c(i2c, &rc5t583_regmap_config);
	if (IS_ERR(rc5t583->regmap)) {
		ret = PTR_ERR(rc5t583->regmap);
		dev_err(&i2c->dev, "regmap initialization failed: %d\n", ret);
		return ret;
	}

	ret = rc5t583_clear_ext_power_req(rc5t583, pdata);
	if (ret < 0)
		return ret;

	if (i2c->irq) {
		ret = rc5t583_irq_init(rc5t583, i2c->irq, pdata->irq_base);
		/* Still continue with warning, if irq init fails */
		if (ret)
			dev_warn(&i2c->dev, "IRQ init failed: %d\n", ret);
	}

	ret = devm_mfd_add_devices(rc5t583->dev, -1, rc5t583_subdevs,
				   ARRAY_SIZE(rc5t583_subdevs), NULL, 0, NULL);
	if (ret) {
		dev_err(&i2c->dev, "add mfd devices failed: %d\n", ret);
		return ret;
	}

	return 0;
}