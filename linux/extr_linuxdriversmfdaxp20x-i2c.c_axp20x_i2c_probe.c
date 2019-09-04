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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_cfg; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int axp20x_device_probe (struct axp20x_dev*) ; 
 int axp20x_match_device (struct axp20x_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct axp20x_dev*) ; 
 struct axp20x_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct axp20x_dev *axp20x;
	int ret;

	axp20x = devm_kzalloc(&i2c->dev, sizeof(*axp20x), GFP_KERNEL);
	if (!axp20x)
		return -ENOMEM;

	axp20x->dev = &i2c->dev;
	axp20x->irq = i2c->irq;
	dev_set_drvdata(axp20x->dev, axp20x);

	ret = axp20x_match_device(axp20x);
	if (ret)
		return ret;

	axp20x->regmap = devm_regmap_init_i2c(i2c, axp20x->regmap_cfg);
	if (IS_ERR(axp20x->regmap)) {
		ret = PTR_ERR(axp20x->regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	return axp20x_device_probe(axp20x);
}