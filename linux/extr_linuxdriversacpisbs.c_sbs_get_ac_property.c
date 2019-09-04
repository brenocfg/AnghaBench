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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct acpi_sbs {int /*<<< orphan*/  charger_present; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 struct acpi_sbs* to_acpi_sbs (struct power_supply*) ; 

__attribute__((used)) static int sbs_get_ac_property(struct power_supply *psy,
			       enum power_supply_property psp,
			       union power_supply_propval *val)
{
	struct acpi_sbs *sbs = to_acpi_sbs(psy);
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = sbs->charger_present;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}