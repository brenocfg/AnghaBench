#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* properties; int num_properties; int use_for_apm; int /*<<< orphan*/  external_power_changed; int /*<<< orphan*/  get_property; int /*<<< orphan*/  type; scalar_t__ name; } ;
struct z2_charger {TYPE_2__ batt_ps_desc; TYPE_1__* client; struct z2_battery_info* info; } ;
struct z2_battery_info {scalar_t__ charge_gpio; scalar_t__ batt_tech; scalar_t__ batt_I2C_reg; scalar_t__ max_voltage; scalar_t__ min_voltage; scalar_t__ batt_name; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int POWER_SUPPLY_PROP_PRESENT ; 
 int POWER_SUPPLY_PROP_STATUS ; 
 int POWER_SUPPLY_PROP_TECHNOLOGY ; 
 int POWER_SUPPLY_PROP_VOLTAGE_MAX ; 
 int POWER_SUPPLY_PROP_VOLTAGE_MIN ; 
 int POWER_SUPPLY_PROP_VOLTAGE_NOW ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 scalar_t__ Z2_DEFAULT_NAME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z2_batt_ext_power_changed ; 
 int /*<<< orphan*/  z2_batt_get_property ; 

__attribute__((used)) static int z2_batt_ps_init(struct z2_charger *charger, int props)
{
	int i = 0;
	enum power_supply_property *prop;
	struct z2_battery_info *info = charger->info;

	if (info->charge_gpio >= 0)
		props++;	/* POWER_SUPPLY_PROP_STATUS */
	if (info->batt_tech >= 0)
		props++;	/* POWER_SUPPLY_PROP_TECHNOLOGY */
	if (info->batt_I2C_reg >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_NOW */
	if (info->max_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MAX */
	if (info->min_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MIN */

	prop = kcalloc(props, sizeof(*prop), GFP_KERNEL);
	if (!prop)
		return -ENOMEM;

	prop[i++] = POWER_SUPPLY_PROP_PRESENT;
	if (info->charge_gpio >= 0)
		prop[i++] = POWER_SUPPLY_PROP_STATUS;
	if (info->batt_tech >= 0)
		prop[i++] = POWER_SUPPLY_PROP_TECHNOLOGY;
	if (info->batt_I2C_reg >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_NOW;
	if (info->max_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MAX;
	if (info->min_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MIN;

	if (!info->batt_name) {
		dev_info(&charger->client->dev,
				"Please consider setting proper battery "
				"name in platform definition file, falling "
				"back to name \" Z2_DEFAULT_NAME \"\n");
		charger->batt_ps_desc.name = Z2_DEFAULT_NAME;
	} else
		charger->batt_ps_desc.name = info->batt_name;

	charger->batt_ps_desc.properties	= prop;
	charger->batt_ps_desc.num_properties	= props;
	charger->batt_ps_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	charger->batt_ps_desc.get_property	= z2_batt_get_property;
	charger->batt_ps_desc.external_power_changed =
						z2_batt_ext_power_changed;
	charger->batt_ps_desc.use_for_apm	= 1;

	return 0;
}