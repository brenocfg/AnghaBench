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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 size_t TEST_BATTERY ; 
 int /*<<< orphan*/  battery_health ; 
 int /*<<< orphan*/  map_get_value (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_health ; 
 int /*<<< orphan*/  signal_power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_power_supplies ; 

__attribute__((used)) static int param_set_battery_health(const char *key,
					const struct kernel_param *kp)
{
	battery_health = map_get_value(map_health, key, battery_health);
	signal_power_supply_changed(test_power_supplies[TEST_BATTERY]);
	return 0;
}