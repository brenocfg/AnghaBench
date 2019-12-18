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
struct exynos_lpass {int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_lpass_disable (struct exynos_lpass*) ; 
 struct exynos_lpass* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_lpass_remove(struct platform_device *pdev)
{
	struct exynos_lpass *lpass = platform_get_drvdata(pdev);

	exynos_lpass_disable(lpass);
	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		exynos_lpass_disable(lpass);
	regmap_exit(lpass->top);

	return 0;
}