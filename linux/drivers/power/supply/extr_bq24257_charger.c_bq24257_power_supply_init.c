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
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; int /*<<< orphan*/  attr_grp; struct bq24257_device* drv_data; } ;
struct bq24257_device {int /*<<< orphan*/  charger; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq24257_charger_supplied_to ; 
 int /*<<< orphan*/  bq24257_charger_sysfs_groups ; 
 int /*<<< orphan*/  bq24257_power_supply_desc ; 
 int /*<<< orphan*/  devm_power_supply_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct power_supply_config*) ; 

__attribute__((used)) static int bq24257_power_supply_init(struct bq24257_device *bq)
{
	struct power_supply_config psy_cfg = { .drv_data = bq, };

	psy_cfg.attr_grp = bq24257_charger_sysfs_groups;
	psy_cfg.supplied_to = bq24257_charger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(bq24257_charger_supplied_to);

	bq->charger = devm_power_supply_register(bq->dev,
						 &bq24257_power_supply_desc,
						 &psy_cfg);

	return PTR_ERR_OR_ZERO(bq->charger);
}