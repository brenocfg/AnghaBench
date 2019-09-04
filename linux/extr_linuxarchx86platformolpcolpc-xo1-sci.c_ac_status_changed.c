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

/* Variables and functions */
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 struct power_supply* power_supply_get_by_name (char*) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 

__attribute__((used)) static void ac_status_changed(void)
{
	struct power_supply *psy = power_supply_get_by_name("olpc-ac");

	if (psy) {
		power_supply_changed(psy);
		power_supply_put(psy);
	}
}