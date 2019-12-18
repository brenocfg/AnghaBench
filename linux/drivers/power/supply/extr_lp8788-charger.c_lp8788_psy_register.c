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
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; int /*<<< orphan*/  attr_grp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lp8788_charger {void* charger; void* battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EPERM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  battery_supplied_to ; 
 int /*<<< orphan*/  lp8788_charger_sysfs_groups ; 
 int /*<<< orphan*/  lp8788_psy_battery_desc ; 
 int /*<<< orphan*/  lp8788_psy_charger_desc ; 
 void* power_supply_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (void*) ; 

__attribute__((used)) static int lp8788_psy_register(struct platform_device *pdev,
				struct lp8788_charger *pchg)
{
	struct power_supply_config charger_cfg = {};

	charger_cfg.attr_grp = lp8788_charger_sysfs_groups;
	charger_cfg.supplied_to = battery_supplied_to;
	charger_cfg.num_supplicants = ARRAY_SIZE(battery_supplied_to);

	pchg->charger = power_supply_register(&pdev->dev,
					      &lp8788_psy_charger_desc,
					      &charger_cfg);
	if (IS_ERR(pchg->charger))
		return -EPERM;

	pchg->battery = power_supply_register(&pdev->dev,
					      &lp8788_psy_battery_desc, NULL);
	if (IS_ERR(pchg->battery)) {
		power_supply_unregister(pchg->charger);
		return -EPERM;
	}

	return 0;
}