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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct iommu_group {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct tegra_smmu* iommu; } ;
struct device {TYPE_1__ archdata; struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 scalar_t__ of_parse_phandle_with_args (struct device_node*,char*,char*,unsigned int,struct of_phandle_args*) ; 
 int tegra_smmu_configure (struct tegra_smmu*,struct device*,struct of_phandle_args*) ; 
 struct tegra_smmu* tegra_smmu_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_smmu_add_device(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct tegra_smmu *smmu = NULL;
	struct iommu_group *group;
	struct of_phandle_args args;
	unsigned int index = 0;
	int err;

	while (of_parse_phandle_with_args(np, "iommus", "#iommu-cells", index,
					  &args) == 0) {
		smmu = tegra_smmu_find(args.np);
		if (smmu) {
			err = tegra_smmu_configure(smmu, dev, &args);
			of_node_put(args.np);

			if (err < 0)
				return err;

			/*
			 * Only a single IOMMU master interface is currently
			 * supported by the Linux kernel, so abort after the
			 * first match.
			 */
			dev->archdata.iommu = smmu;

			iommu_device_link(&smmu->iommu, dev);

			break;
		}

		of_node_put(args.np);
		index++;
	}

	if (!smmu)
		return -ENODEV;

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);

	iommu_group_put(group);

	return 0;
}