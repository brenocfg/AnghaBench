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
typedef  enum hwmon_sensor_types { ____Placeholder_hwmon_sensor_types } hwmon_sensor_types ;

/* Variables and functions */
#define  hwmon_in 129 
#define  hwmon_power 128 
 int /*<<< orphan*/  hwmon_power_average_interval ; 
 int /*<<< orphan*/ * lochnagar_chan_names ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static umode_t lochnagar_is_visible(const void *drvdata,
				    enum hwmon_sensor_types type,
				    u32 attr, int chan)
{
	switch (type) {
	case hwmon_in:
		if (!strcmp("SYSVDD", lochnagar_chan_names[chan]))
			return 0;
		break;
	case hwmon_power:
		if (attr == hwmon_power_average_interval)
			return 0644;
		break;
	default:
		break;
	}

	return 0444;
}