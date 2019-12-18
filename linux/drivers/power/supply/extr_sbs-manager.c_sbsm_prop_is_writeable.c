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
struct sbsm_data {scalar_t__ is_ltc1760; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int POWER_SUPPLY_PROP_CHARGE_TYPE ; 
 struct sbsm_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int sbsm_prop_is_writeable(struct power_supply *psy,
				  enum power_supply_property psp)
{
	struct sbsm_data *data = power_supply_get_drvdata(psy);

	return (psp == POWER_SUPPLY_PROP_CHARGE_TYPE) && data->is_ltc1760;
}