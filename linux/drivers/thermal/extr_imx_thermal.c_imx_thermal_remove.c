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
struct regmap {int dummy; } ;
struct platform_device {int dummy; } ;
struct imx_thermal_data {int /*<<< orphan*/  policy; int /*<<< orphan*/  cdev; int /*<<< orphan*/  tz; int /*<<< orphan*/  thermal_clk; TYPE_1__* socdata; struct regmap* tempmon; } ;
struct TYPE_2__ {int /*<<< orphan*/  power_down_mask; scalar_t__ sensor_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_SET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cooling_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (int /*<<< orphan*/ ) ; 
 struct imx_thermal_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_thermal_remove(struct platform_device *pdev)
{
	struct imx_thermal_data *data = platform_get_drvdata(pdev);
	struct regmap *map = data->tempmon;

	/* Disable measurements */
	regmap_write(map, data->socdata->sensor_ctrl + REG_SET,
		     data->socdata->power_down_mask);
	if (!IS_ERR(data->thermal_clk))
		clk_disable_unprepare(data->thermal_clk);

	thermal_zone_device_unregister(data->tz);
	cpufreq_cooling_unregister(data->cdev);
	cpufreq_cpu_put(data->policy);

	return 0;
}