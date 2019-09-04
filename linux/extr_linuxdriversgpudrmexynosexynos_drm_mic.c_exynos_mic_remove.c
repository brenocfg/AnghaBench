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
struct exynos_mic {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_mic_component_ops ; 
 struct exynos_mic* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_mic_remove(struct platform_device *pdev)
{
	struct exynos_mic *mic = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &exynos_mic_component_ops);
	pm_runtime_disable(&pdev->dev);

	drm_bridge_remove(&mic->bridge);

	return 0;
}