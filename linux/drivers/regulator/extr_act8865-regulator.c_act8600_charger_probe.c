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
struct regmap {int dummy; } ;
struct power_supply_config {int /*<<< orphan*/  of_node; struct regmap* drv_data; } ;
struct power_supply {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct power_supply*) ; 
 int /*<<< orphan*/  act8600_charger_desc ; 
 struct power_supply* devm_power_supply_register (struct device*,int /*<<< orphan*/ *,struct power_supply_config*) ; 

__attribute__((used)) static int act8600_charger_probe(struct device *dev, struct regmap *regmap)
{
	struct power_supply *charger;
	struct power_supply_config cfg = {
		.drv_data = regmap,
		.of_node = dev->of_node,
	};

	charger = devm_power_supply_register(dev, &act8600_charger_desc, &cfg);

	return PTR_ERR_OR_ZERO(charger);
}