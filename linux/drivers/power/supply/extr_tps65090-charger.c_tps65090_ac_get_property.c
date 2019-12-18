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
struct tps65090_charger {int /*<<< orphan*/  ac_online; int /*<<< orphan*/  prev_ac_online; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_PROP_ONLINE ; 
 struct tps65090_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int tps65090_ac_get_property(struct power_supply *psy,
			enum power_supply_property psp,
			union power_supply_propval *val)
{
	struct tps65090_charger *charger = power_supply_get_drvdata(psy);

	if (psp == POWER_SUPPLY_PROP_ONLINE) {
		val->intval = charger->ac_online;
		charger->prev_ac_online = charger->ac_online;
		return 0;
	}
	return -EINVAL;
}