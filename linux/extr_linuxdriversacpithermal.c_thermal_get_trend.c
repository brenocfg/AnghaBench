#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct TYPE_3__ {int tc1; int tc2; int temperature; } ;
struct TYPE_4__ {TYPE_1__ passive; } ;
struct acpi_thermal {int temperature; int last_temperature; TYPE_2__ trips; int /*<<< orphan*/  kelvin_offset; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;

/* Variables and functions */
 int DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int THERMAL_TREND_DROPPING ; 
 int THERMAL_TREND_RAISING ; 
 int THERMAL_TREND_STABLE ; 
 int THERMAL_TRIP_ACTIVE ; 
 scalar_t__ thermal_get_trip_temp (struct thermal_zone_device*,int,int*) ; 
 scalar_t__ thermal_get_trip_type (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int thermal_get_trend(struct thermal_zone_device *thermal,
				int trip, enum thermal_trend *trend)
{
	struct acpi_thermal *tz = thermal->devdata;
	enum thermal_trip_type type;
	int i;

	if (thermal_get_trip_type(thermal, trip, &type))
		return -EINVAL;

	if (type == THERMAL_TRIP_ACTIVE) {
		int trip_temp;
		int temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
					tz->temperature, tz->kelvin_offset);
		if (thermal_get_trip_temp(thermal, trip, &trip_temp))
			return -EINVAL;

		if (temp > trip_temp) {
			*trend = THERMAL_TREND_RAISING;
			return 0;
		} else {
			/* Fall back on default trend */
			return -EINVAL;
		}
	}

	/*
	 * tz->temperature has already been updated by generic thermal layer,
	 * before this callback being invoked
	 */
	i = (tz->trips.passive.tc1 * (tz->temperature - tz->last_temperature))
		+ (tz->trips.passive.tc2
		* (tz->temperature - tz->trips.passive.temperature));

	if (i > 0)
		*trend = THERMAL_TREND_RAISING;
	else if (i < 0)
		*trend = THERMAL_TREND_DROPPING;
	else
		*trend = THERMAL_TREND_STABLE;
	return 0;
}