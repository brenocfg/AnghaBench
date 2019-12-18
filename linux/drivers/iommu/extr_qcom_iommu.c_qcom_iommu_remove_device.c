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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_fwspec_free (struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 struct qcom_iommu_dev* to_iommu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_iommu_remove_device(struct device *dev)
{
	struct qcom_iommu_dev *qcom_iommu = to_iommu(dev_iommu_fwspec_get(dev));

	if (!qcom_iommu)
		return;

	iommu_device_unlink(&qcom_iommu->iommu, dev);
	iommu_group_remove_device(dev);
	iommu_fwspec_free(dev);
}