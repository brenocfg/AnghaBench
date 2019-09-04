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
struct tegra_smmu {int /*<<< orphan*/  debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_smmu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_smmu_clients_fops ; 
 int /*<<< orphan*/  tegra_smmu_swgroups_fops ; 

__attribute__((used)) static void tegra_smmu_debugfs_init(struct tegra_smmu *smmu)
{
	smmu->debugfs = debugfs_create_dir("smmu", NULL);
	if (!smmu->debugfs)
		return;

	debugfs_create_file("swgroups", S_IRUGO, smmu->debugfs, smmu,
			    &tegra_smmu_swgroups_fops);
	debugfs_create_file("clients", S_IRUGO, smmu->debugfs, smmu,
			    &tegra_smmu_clients_fops);
}