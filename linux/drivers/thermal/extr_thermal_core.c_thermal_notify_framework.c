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
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_thermal_trip (struct thermal_zone_device*,int) ; 

void thermal_notify_framework(struct thermal_zone_device *tz, int trip)
{
	handle_thermal_trip(tz, trip);
}