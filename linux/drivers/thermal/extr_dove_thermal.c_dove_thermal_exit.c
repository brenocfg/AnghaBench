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
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct thermal_zone_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (struct thermal_zone_device*) ; 

__attribute__((used)) static int dove_thermal_exit(struct platform_device *pdev)
{
	struct thermal_zone_device *dove_thermal =
		platform_get_drvdata(pdev);

	thermal_zone_device_unregister(dove_thermal);

	return 0;
}