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
struct qcom_iommu_dev {int /*<<< orphan*/  iommu; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 struct qcom_iommu_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_iommu_device_remove(struct platform_device *pdev)
{
	struct qcom_iommu_dev *qcom_iommu = platform_get_drvdata(pdev);

	bus_set_iommu(&platform_bus_type, NULL);

	pm_runtime_force_suspend(&pdev->dev);
	platform_set_drvdata(pdev, NULL);
	iommu_device_sysfs_remove(&qcom_iommu->iommu);
	iommu_device_unregister(&qcom_iommu->iommu);

	return 0;
}