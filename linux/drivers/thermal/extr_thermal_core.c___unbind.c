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
struct thermal_zone_device {int trips; } ;
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_unbind_cooling_device (struct thermal_zone_device*,int,struct thermal_cooling_device*) ; 

__attribute__((used)) static void __unbind(struct thermal_zone_device *tz, int mask,
		     struct thermal_cooling_device *cdev)
{
	int i;

	for (i = 0; i < tz->trips; i++)
		if (mask & (1 << i))
			thermal_zone_unbind_cooling_device(tz, i, cdev);
}