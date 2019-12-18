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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct power_supply_hwmon {int /*<<< orphan*/  psy; int /*<<< orphan*/  props; } ;
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
 scalar_t__ power_supply_hwmon_is_a_label (int,int /*<<< orphan*/ ) ; 
 scalar_t__ power_supply_hwmon_is_writable (int,int /*<<< orphan*/ ) ; 
 int power_supply_hwmon_to_property (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ power_supply_property_is_writeable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static umode_t power_supply_hwmon_is_visible(const void *data,
					     enum hwmon_sensor_types type,
					     u32 attr, int channel)
{
	const struct power_supply_hwmon *psyhw = data;
	int prop;


	if (power_supply_hwmon_is_a_label(type, attr))
		return 0444;

	prop = power_supply_hwmon_to_property(type, attr, channel);
	if (prop < 0 || !test_bit(prop, psyhw->props))
		return 0;

	if (power_supply_property_is_writeable(psyhw->psy, prop) > 0 &&
	    power_supply_hwmon_is_writable(type, attr))
		return 0644;

	return 0444;
}