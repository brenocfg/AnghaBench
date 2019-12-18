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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dwc3_exynos {int num_clks; size_t suspend_clk_idx; int /*<<< orphan*/  vdd10; int /*<<< orphan*/  vdd33; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_exynos_remove_child ; 
 struct dwc3_exynos* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_exynos_remove(struct platform_device *pdev)
{
	struct dwc3_exynos	*exynos = platform_get_drvdata(pdev);
	int i;

	device_for_each_child(&pdev->dev, NULL, dwc3_exynos_remove_child);

	for (i = exynos->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(exynos->clks[i]);

	if (exynos->suspend_clk_idx >= 0)
		clk_disable_unprepare(exynos->clks[exynos->suspend_clk_idx]);

	regulator_disable(exynos->vdd33);
	regulator_disable(exynos->vdd10);

	return 0;
}