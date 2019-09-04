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
struct platform_device {int dummy; } ;
struct gart_device {scalar_t__ savedata; scalar_t__ regs; int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 scalar_t__ GART_CONFIG ; 
 int /*<<< orphan*/ * gart_handle ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 struct gart_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_gart_remove(struct platform_device *pdev)
{
	struct gart_device *gart = platform_get_drvdata(pdev);

	iommu_device_unregister(&gart->iommu);
	iommu_device_sysfs_remove(&gart->iommu);

	writel(0, gart->regs + GART_CONFIG);
	if (gart->savedata)
		vfree(gart->savedata);
	gart_handle = NULL;
	return 0;
}