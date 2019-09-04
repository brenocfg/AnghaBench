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
typedef  int /*<<< orphan*/  u8 ;
struct steam_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  battery_charge; int /*<<< orphan*/  voltage; int /*<<< orphan*/  battery; } ;
struct power_supply {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ likely (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 struct power_supply* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  steam_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void steam_do_battery_event(struct steam_device *steam,
		struct power_supply *battery, u8 *data)
{
	unsigned long flags;

	s16 volts = steam_le16(data + 12);
	u8 batt = data[14];

	/* Creating the battery may have failed */
	rcu_read_lock();
	battery = rcu_dereference(steam->battery);
	if (likely(battery)) {
		spin_lock_irqsave(&steam->lock, flags);
		steam->voltage = volts;
		steam->battery_charge = batt;
		spin_unlock_irqrestore(&steam->lock, flags);
		power_supply_changed(battery);
	}
	rcu_read_unlock();
}