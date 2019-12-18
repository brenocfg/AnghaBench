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
struct power_supply {int dummy; } ;
struct TYPE_2__ {size_t num_properties; int /*<<< orphan*/ * properties; } ;
struct charger_manager {struct charger_desc* desc; TYPE_1__ charger_psy_desc; int /*<<< orphan*/  tzd_batt; } ;
struct charger_desc {int measure_battery_temp; scalar_t__ temp_diff; scalar_t__ temp_max; scalar_t__ thermal_zone; } ;

/* Variables and functions */
 scalar_t__ CM_DEFAULT_CHARGE_TEMP_MAX ; 
 scalar_t__ CM_DEFAULT_RECHARGE_TEMP_DIFF ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_TEMP ; 
 int /*<<< orphan*/  POWER_SUPPLY_PROP_TEMP_AMBIENT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int power_supply_get_property (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int /*<<< orphan*/  thermal_zone_get_zone_by_name (scalar_t__) ; 

__attribute__((used)) static int cm_init_thermal_data(struct charger_manager *cm,
		struct power_supply *fuel_gauge)
{
	struct charger_desc *desc = cm->desc;
	union power_supply_propval val;
	int ret;

	/* Verify whether fuel gauge provides battery temperature */
	ret = power_supply_get_property(fuel_gauge,
					POWER_SUPPLY_PROP_TEMP, &val);

	if (!ret) {
		cm->charger_psy_desc.properties[cm->charger_psy_desc.num_properties] =
				POWER_SUPPLY_PROP_TEMP;
		cm->charger_psy_desc.num_properties++;
		cm->desc->measure_battery_temp = true;
	}
#ifdef CONFIG_THERMAL
	if (ret && desc->thermal_zone) {
		cm->tzd_batt =
			thermal_zone_get_zone_by_name(desc->thermal_zone);
		if (IS_ERR(cm->tzd_batt))
			return PTR_ERR(cm->tzd_batt);

		/* Use external thermometer */
		cm->charger_psy_desc.properties[cm->charger_psy_desc.num_properties] =
				POWER_SUPPLY_PROP_TEMP_AMBIENT;
		cm->charger_psy_desc.num_properties++;
		cm->desc->measure_battery_temp = true;
		ret = 0;
	}
#endif
	if (cm->desc->measure_battery_temp) {
		/* NOTICE : Default allowable minimum charge temperature is 0 */
		if (!desc->temp_max)
			desc->temp_max = CM_DEFAULT_CHARGE_TEMP_MAX;
		if (!desc->temp_diff)
			desc->temp_diff = CM_DEFAULT_RECHARGE_TEMP_DIFF;
	}

	return ret;
}