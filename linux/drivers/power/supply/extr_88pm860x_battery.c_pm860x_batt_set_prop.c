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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct pm860x_battery_info {int start_soc; int /*<<< orphan*/  dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EPERM ; 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 128 
 int /*<<< orphan*/  ccnt_data ; 
 int /*<<< orphan*/  clear_ccnt (struct pm860x_battery_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct pm860x_battery_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_batt_set_prop(struct power_supply *psy,
				       enum power_supply_property psp,
				       const union power_supply_propval *val)
{
	struct pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		clear_ccnt(info, &ccnt_data);
		info->start_soc = 100;
		dev_dbg(info->dev, "chg done, update soc = %d\n",
			info->start_soc);
		break;
	default:
		return -EPERM;
	}

	return 0;
}