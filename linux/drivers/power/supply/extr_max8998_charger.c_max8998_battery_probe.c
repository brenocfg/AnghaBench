#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct max8998_battery_data* drv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max8998_platform_data {int eoc; int restart; int timeout; } ;
struct max8998_dev {struct i2c_client* i2c; struct max8998_platform_data* pdata; } ;
struct max8998_battery_data {TYPE_1__* dev; int /*<<< orphan*/  battery; struct max8998_dev* iodev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX8998_REG_CHGR1 ; 
 int /*<<< orphan*/  MAX8998_REG_CHGR2 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max8998_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct max8998_battery_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  max8998_battery_desc ; 
 int /*<<< orphan*/  max8998_update_reg (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max8998_battery_data*) ; 

__attribute__((used)) static int max8998_battery_probe(struct platform_device *pdev)
{
	struct max8998_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max8998_platform_data *pdata = iodev->pdata;
	struct power_supply_config psy_cfg = {};
	struct max8998_battery_data *max8998;
	struct i2c_client *i2c;
	int ret = 0;

	if (!pdata) {
		dev_err(pdev->dev.parent, "No platform init data supplied\n");
		return -ENODEV;
	}

	max8998 = devm_kzalloc(&pdev->dev, sizeof(struct max8998_battery_data),
				GFP_KERNEL);
	if (!max8998)
		return -ENOMEM;

	max8998->dev = &pdev->dev;
	max8998->iodev = iodev;
	platform_set_drvdata(pdev, max8998);
	i2c = max8998->iodev->i2c;

	/* Setup "End of Charge" */
	/* If EOC value equals 0,
	 * remain value set from bootloader or default value */
	if (pdata->eoc >= 10 && pdata->eoc <= 45) {
		max8998_update_reg(i2c, MAX8998_REG_CHGR1,
				(pdata->eoc / 5 - 2) << 5, 0x7 << 5);
	} else if (pdata->eoc == 0) {
		dev_dbg(max8998->dev,
			"EOC value not set: leave it unchanged.\n");
	} else {
		dev_err(max8998->dev, "Invalid EOC value\n");
		return -EINVAL;
	}

	/* Setup Charge Restart Level */
	switch (pdata->restart) {
	case 100:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x1 << 3, 0x3 << 3);
		break;
	case 150:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x0 << 3, 0x3 << 3);
		break;
	case 200:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x2 << 3, 0x3 << 3);
		break;
	case -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR1, 0x3 << 3, 0x3 << 3);
		break;
	case 0:
		dev_dbg(max8998->dev,
			"Restart Level not set: leave it unchanged.\n");
		break;
	default:
		dev_err(max8998->dev, "Invalid Restart Level\n");
		return -EINVAL;
	}

	/* Setup Charge Full Timeout */
	switch (pdata->timeout) {
	case 5:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x0 << 4, 0x3 << 4);
		break;
	case 6:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x1 << 4, 0x3 << 4);
		break;
	case 7:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x2 << 4, 0x3 << 4);
		break;
	case -1:
		max8998_update_reg(i2c, MAX8998_REG_CHGR2, 0x3 << 4, 0x3 << 4);
		break;
	case 0:
		dev_dbg(max8998->dev,
			"Full Timeout not set: leave it unchanged.\n");
		break;
	default:
		dev_err(max8998->dev, "Invalid Full Timeout value\n");
		return -EINVAL;
	}

	psy_cfg.drv_data = max8998;

	max8998->battery = devm_power_supply_register(max8998->dev,
						      &max8998_battery_desc,
						      &psy_cfg);
	if (IS_ERR(max8998->battery)) {
		ret = PTR_ERR(max8998->battery);
		dev_err(max8998->dev, "failed: power supply register: %d\n",
			ret);
		return ret;
	}

	return 0;
}