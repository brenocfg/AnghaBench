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
struct gb_power_supply {int /*<<< orphan*/  psy; scalar_t__ registered; int /*<<< orphan*/  work; scalar_t__ update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gb_power_supply_free (struct gb_power_supply*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _gb_power_supply_release(struct gb_power_supply *gbpsy)
{
	gbpsy->update_interval = 0;

	cancel_delayed_work_sync(&gbpsy->work);

	if (gbpsy->registered)
		power_supply_unregister(gbpsy->psy);

	_gb_power_supply_free(gbpsy);
}