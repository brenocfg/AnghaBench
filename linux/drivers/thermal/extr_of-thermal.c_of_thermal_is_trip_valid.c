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
struct thermal_zone_device {struct __thermal_zone* devdata; } ;
struct __thermal_zone {int ntrips; } ;

/* Variables and functions */

bool of_thermal_is_trip_valid(struct thermal_zone_device *tz, int trip)
{
	struct __thermal_zone *data = tz->devdata;

	if (!data || trip >= data->ntrips || trip < 0)
		return false;

	return true;
}