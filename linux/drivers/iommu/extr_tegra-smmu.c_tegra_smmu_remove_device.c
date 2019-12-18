#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_smmu {int /*<<< orphan*/  iommu; } ;
struct TYPE_2__ {struct tegra_smmu* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 

__attribute__((used)) static void tegra_smmu_remove_device(struct device *dev)
{
	struct tegra_smmu *smmu = dev->archdata.iommu;

	if (smmu)
		iommu_device_unlink(&smmu->iommu, dev);

	dev->archdata.iommu = NULL;
	iommu_group_remove_device(dev);
}