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
struct tegra_smmu {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_smmu_debugfs_exit (struct tegra_smmu*) ; 

void tegra_smmu_remove(struct tegra_smmu *smmu)
{
	iommu_device_unregister(&smmu->iommu);
	iommu_device_sysfs_remove(&smmu->iommu);

	if (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_smmu_debugfs_exit(smmu);
}