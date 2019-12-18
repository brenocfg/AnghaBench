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
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct asus_drvdata {int battery_stat; int battery_capacity; TYPE_1__* hdev; scalar_t__ battery_next_query; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 132 
#define  POWER_SUPPLY_PROP_MODEL_NAME 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_SCOPE 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int POWER_SUPPLY_SCOPE_DEVICE ; 
 scalar_t__ QUERY_MIN_INTERVAL ; 
 int asus_battery_query (struct asus_drvdata*) ; 
 scalar_t__ jiffies ; 
 struct asus_drvdata* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int asus_battery_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct asus_drvdata *drvdata = power_supply_get_drvdata(psy);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
	case POWER_SUPPLY_PROP_CAPACITY:
		if (time_before(drvdata->battery_next_query, jiffies)) {
			drvdata->battery_next_query =
					 jiffies + QUERY_MIN_INTERVAL;
			ret = asus_battery_query(drvdata);
			if (ret)
				return ret;
		}
		if (psp == POWER_SUPPLY_PROP_STATUS)
			val->intval = drvdata->battery_stat;
		else
			val->intval = drvdata->battery_capacity;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_DEVICE;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = drvdata->hdev->name;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}