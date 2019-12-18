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
struct exynos_tmu_data {int /*<<< orphan*/  regulator; int /*<<< orphan*/  clk_sec; int /*<<< orphan*/  clk; int /*<<< orphan*/  sclk; struct thermal_zone_device* tzd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_tmu_control (struct platform_device*,int) ; 
 struct exynos_tmu_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,struct thermal_zone_device*) ; 

__attribute__((used)) static int exynos_tmu_remove(struct platform_device *pdev)
{
	struct exynos_tmu_data *data = platform_get_drvdata(pdev);
	struct thermal_zone_device *tzd = data->tzd;

	thermal_zone_of_sensor_unregister(&pdev->dev, tzd);
	exynos_tmu_control(pdev, false);

	clk_disable_unprepare(data->sclk);
	clk_unprepare(data->clk);
	if (!IS_ERR(data->clk_sec))
		clk_unprepare(data->clk_sec);

	if (!IS_ERR(data->regulator))
		regulator_disable(data->regulator);

	return 0;
}