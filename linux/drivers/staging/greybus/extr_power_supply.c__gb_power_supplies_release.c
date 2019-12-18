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
struct gb_power_supplies {int supplies_count; int /*<<< orphan*/  supplies_lock; struct gb_power_supplies* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gb_power_supply_release (struct gb_power_supplies*) ; 
 int /*<<< orphan*/  kfree (struct gb_power_supplies*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _gb_power_supplies_release(struct gb_power_supplies *supplies)
{
	int i;

	if (!supplies->supply)
		return;

	mutex_lock(&supplies->supplies_lock);
	for (i = 0; i < supplies->supplies_count; i++)
		_gb_power_supply_release(&supplies->supply[i]);
	kfree(supplies->supply);
	mutex_unlock(&supplies->supplies_lock);
	kfree(supplies);
}