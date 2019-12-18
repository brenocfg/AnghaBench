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
struct zx2967_thermal_priv {int /*<<< orphan*/  clk_apb; int /*<<< orphan*/  clk_topcrm; int /*<<< orphan*/  tzd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct zx2967_thermal_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx2967_thermal_exit(struct platform_device *pdev)
{
	struct zx2967_thermal_priv *priv = platform_get_drvdata(pdev);

	thermal_zone_of_sensor_unregister(&pdev->dev, priv->tzd);
	clk_disable_unprepare(priv->clk_topcrm);
	clk_disable_unprepare(priv->clk_apb);

	return 0;
}