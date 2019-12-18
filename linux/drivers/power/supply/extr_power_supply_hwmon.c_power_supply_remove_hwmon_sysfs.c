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
struct power_supply {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_add_hwmon_sysfs ; 

void power_supply_remove_hwmon_sysfs(struct power_supply *psy)
{
	devres_release_group(&psy->dev, power_supply_add_hwmon_sysfs);
}