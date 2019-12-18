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
struct max77693_dev {int /*<<< orphan*/  i2c_chg; int /*<<< orphan*/  regmap_chg; TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR_CHG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (int /*<<< orphan*/ ,struct max77693_dev*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max77843_charger_regmap_config ; 

__attribute__((used)) static int max77843_chg_init(struct max77693_dev *max77843)
{
	int ret;

	max77843->i2c_chg = i2c_new_dummy_device(max77843->i2c->adapter, I2C_ADDR_CHG);
	if (IS_ERR(max77843->i2c_chg)) {
		dev_err(&max77843->i2c->dev,
				"Cannot allocate I2C device for Charger\n");
		return PTR_ERR(max77843->i2c_chg);
	}
	i2c_set_clientdata(max77843->i2c_chg, max77843);

	max77843->regmap_chg = devm_regmap_init_i2c(max77843->i2c_chg,
			&max77843_charger_regmap_config);
	if (IS_ERR(max77843->regmap_chg)) {
		ret = PTR_ERR(max77843->regmap_chg);
		goto err_chg_i2c;
	}

	return 0;

err_chg_i2c:
	i2c_unregister_device(max77843->i2c_chg);

	return ret;
}