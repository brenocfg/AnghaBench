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
struct power_supply {int dummy; } ;
struct axp288_fg_info {int /*<<< orphan*/  bat; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 struct axp288_fg_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static void fuel_gauge_external_power_changed(struct power_supply *psy)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(psy);

	power_supply_changed(info->bat);
}