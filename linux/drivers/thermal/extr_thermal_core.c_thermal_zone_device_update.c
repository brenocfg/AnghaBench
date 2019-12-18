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
struct thermal_zone_device {int notify_event; int trips; TYPE_1__* ops; } ;
typedef  enum thermal_notify_event { ____Placeholder_thermal_notify_event } thermal_notify_event ;
struct TYPE_2__ {int /*<<< orphan*/  get_temp; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_thermal_trip (struct thermal_zone_device*,int) ; 
 int /*<<< orphan*/  in_suspend ; 
 int /*<<< orphan*/  thermal_zone_set_trips (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  update_temperature (struct thermal_zone_device*) ; 

void thermal_zone_device_update(struct thermal_zone_device *tz,
				enum thermal_notify_event event)
{
	int count;

	if (atomic_read(&in_suspend))
		return;

	if (!tz->ops->get_temp)
		return;

	update_temperature(tz);

	thermal_zone_set_trips(tz);

	tz->notify_event = event;

	for (count = 0; count < tz->trips; count++)
		handle_thermal_trip(tz, count);
}