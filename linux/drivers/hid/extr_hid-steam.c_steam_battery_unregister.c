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
struct steam_device {int /*<<< orphan*/  battery; } ;
struct power_supply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_unregister (struct power_supply*) ; 
 struct power_supply* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void steam_battery_unregister(struct steam_device *steam)
{
	struct power_supply *battery;

	rcu_read_lock();
	battery = rcu_dereference(steam->battery);
	rcu_read_unlock();

	if (!battery)
		return;
	RCU_INIT_POINTER(steam->battery, NULL);
	synchronize_rcu();
	power_supply_unregister(battery);
}