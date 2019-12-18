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
union power_supply_propval {int intval; } ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EC_BAT_SOC ; 
 int olpc_bat_get_charge_full_design (union power_supply_propval*) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int olpc_bat_get_charge_now(union power_supply_propval *val)
{
	uint8_t soc;
	union power_supply_propval full;
	int ret;

	ret = olpc_ec_cmd(EC_BAT_SOC, NULL, 0, &soc, 1);
	if (ret)
		return ret;

	ret = olpc_bat_get_charge_full_design(&full);
	if (ret)
		return ret;

	val->intval = soc * (full.intval / 100);
	return 0;
}