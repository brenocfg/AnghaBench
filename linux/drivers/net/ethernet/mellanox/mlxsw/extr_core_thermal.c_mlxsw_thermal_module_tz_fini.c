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
 int /*<<< orphan*/  thermal_zone_device_unregister (struct thermal_zone_device*) ; 

__attribute__((used)) static void mlxsw_thermal_module_tz_fini(struct thermal_zone_device *tzdev)
{
	thermal_zone_device_unregister(tzdev);
}