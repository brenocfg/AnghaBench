#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct bq27xxx_device_info {TYPE_1__ cache; } ;

/* Variables and functions */
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  bq27xxx_battery_dead (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq27xxx_battery_overtemp (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq27xxx_battery_undertemp (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq27xxx_battery_read_health(struct bq27xxx_device_info *di)
{
	/* Unlikely but important to return first */
	if (unlikely(bq27xxx_battery_overtemp(di, di->cache.flags)))
		return POWER_SUPPLY_HEALTH_OVERHEAT;
	if (unlikely(bq27xxx_battery_undertemp(di, di->cache.flags)))
		return POWER_SUPPLY_HEALTH_COLD;
	if (unlikely(bq27xxx_battery_dead(di, di->cache.flags)))
		return POWER_SUPPLY_HEALTH_DEAD;

	return POWER_SUPPLY_HEALTH_GOOD;
}