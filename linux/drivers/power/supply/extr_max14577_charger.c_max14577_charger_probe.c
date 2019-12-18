#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct max14577_charger* drv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct max14577_charger {int /*<<< orphan*/  charger; int /*<<< orphan*/  pdata; struct max14577* max14577; TYPE_1__* dev; } ;
struct max14577 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX ; 
 scalar_t__ MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN ; 
 int MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_fast_charge_timer ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct max14577* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct max14577_charger* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max14577_charger_desc ; 
 int /*<<< orphan*/  max14577_charger_dt_init (struct platform_device*) ; 
 int max14577_charger_reg_init (struct max14577_charger*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max14577_charger*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 

__attribute__((used)) static int max14577_charger_probe(struct platform_device *pdev)
{
	struct max14577_charger *chg;
	struct power_supply_config psy_cfg = {};
	struct max14577 *max14577 = dev_get_drvdata(pdev->dev.parent);
	int ret;

	chg = devm_kzalloc(&pdev->dev, sizeof(*chg), GFP_KERNEL);
	if (!chg)
		return -ENOMEM;

	platform_set_drvdata(pdev, chg);
	chg->dev = &pdev->dev;
	chg->max14577 = max14577;

	chg->pdata = max14577_charger_dt_init(pdev);
	if (IS_ERR_OR_NULL(chg->pdata))
		return PTR_ERR(chg->pdata);

	ret = max14577_charger_reg_init(chg);
	if (ret)
		return ret;

	ret = device_create_file(&pdev->dev, &dev_attr_fast_charge_timer);
	if (ret) {
		dev_err(&pdev->dev, "failed: create sysfs entry\n");
		return ret;
	}

	psy_cfg.drv_data = chg;
	chg->charger = power_supply_register(&pdev->dev, &max14577_charger_desc,
						&psy_cfg);
	if (IS_ERR(chg->charger)) {
		dev_err(&pdev->dev, "failed: power supply register\n");
		ret = PTR_ERR(chg->charger);
		goto err;
	}

	/* Check for valid values for charger */
	BUILD_BUG_ON(MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN +
			MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP * 0xf !=
			MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX);
	return 0;

err:
	device_remove_file(&pdev->dev, &dev_attr_fast_charge_timer);

	return ret;
}