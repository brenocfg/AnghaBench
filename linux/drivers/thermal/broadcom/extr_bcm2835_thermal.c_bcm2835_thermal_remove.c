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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcm2835_thermal_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  debugfsdir; struct thermal_zone_device* tz; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct bcm2835_thermal_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,struct thermal_zone_device*) ; 

__attribute__((used)) static int bcm2835_thermal_remove(struct platform_device *pdev)
{
	struct bcm2835_thermal_data *data = platform_get_drvdata(pdev);
	struct thermal_zone_device *tz = data->tz;

	debugfs_remove_recursive(data->debugfsdir);
	thermal_zone_of_sensor_unregister(&pdev->dev, tz);
	clk_disable_unprepare(data->clk);

	return 0;
}