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
struct gb_power_supply {int changed; int /*<<< orphan*/  update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gb_power_supply_changed (struct gb_power_supply*) ; 
 int /*<<< orphan*/  gb_power_supply_status_get (struct gb_power_supply*) ; 
 int /*<<< orphan*/  update_interval_init ; 

__attribute__((used)) static void gb_power_supply_status_update(struct gb_power_supply *gbpsy)
{
	/* check if there a change that need to be reported */
	gb_power_supply_status_get(gbpsy);

	if (!gbpsy->changed)
		return;

	gbpsy->update_interval = update_interval_init;
	__gb_power_supply_changed(gbpsy);
	gbpsy->changed = false;
}