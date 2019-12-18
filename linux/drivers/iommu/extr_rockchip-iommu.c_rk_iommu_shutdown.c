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
struct rk_iommu {int num_irq; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int,struct rk_iommu*) ; 
 struct rk_iommu* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rk_iommu_shutdown(struct platform_device *pdev)
{
	struct rk_iommu *iommu = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < iommu->num_irq; i++) {
		int irq = platform_get_irq(pdev, i);

		devm_free_irq(iommu->dev, irq, iommu);
	}

	pm_runtime_force_suspend(&pdev->dev);
}