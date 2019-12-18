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
struct omap_iommu {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  iommu; int /*<<< orphan*/ * group; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_iommu_debugfs_remove (struct omap_iommu*) ; 
 struct omap_iommu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_iommu_remove(struct platform_device *pdev)
{
	struct omap_iommu *obj = platform_get_drvdata(pdev);

	if (obj->group) {
		iommu_group_put(obj->group);
		obj->group = NULL;

		iommu_device_sysfs_remove(&obj->iommu);
		iommu_device_unregister(&obj->iommu);
	}

	omap_iommu_debugfs_remove(obj);

	pm_runtime_disable(obj->dev);

	dev_info(&pdev->dev, "%s removed\n", obj->name);
	return 0;
}