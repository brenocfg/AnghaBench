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
struct stm_thermal_sensor {int /*<<< orphan*/  th_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct stm_thermal_sensor* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stm_thermal_sensor_off (struct stm_thermal_sensor*) ; 
 int /*<<< orphan*/  thermal_remove_hwmon_sysfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm_thermal_remove(struct platform_device *pdev)
{
	struct stm_thermal_sensor *sensor = platform_get_drvdata(pdev);

	stm_thermal_sensor_off(sensor);
	thermal_remove_hwmon_sysfs(sensor->th_dev);
	thermal_zone_of_sensor_unregister(&pdev->dev, sensor->th_dev);

	return 0;
}