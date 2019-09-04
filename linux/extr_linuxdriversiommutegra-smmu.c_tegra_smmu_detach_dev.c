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
struct tegra_smmu_as {int /*<<< orphan*/  id; struct tegra_smmu* smmu; } ;
struct tegra_smmu {TYPE_1__* dev; } ;
struct of_phandle_args {unsigned int* args; scalar_t__ np; } ;
struct iommu_domain {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (scalar_t__) ; 
 int /*<<< orphan*/  of_parse_phandle_with_args (struct device_node*,char*,char*,unsigned int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  tegra_smmu_as_unprepare (struct tegra_smmu*,struct tegra_smmu_as*) ; 
 int /*<<< orphan*/  tegra_smmu_disable (struct tegra_smmu*,unsigned int,int /*<<< orphan*/ ) ; 
 struct tegra_smmu_as* to_smmu_as (struct iommu_domain*) ; 

__attribute__((used)) static void tegra_smmu_detach_dev(struct iommu_domain *domain, struct device *dev)
{
	struct tegra_smmu_as *as = to_smmu_as(domain);
	struct device_node *np = dev->of_node;
	struct tegra_smmu *smmu = as->smmu;
	struct of_phandle_args args;
	unsigned int index = 0;

	while (!of_parse_phandle_with_args(np, "iommus", "#iommu-cells", index,
					   &args)) {
		unsigned int swgroup = args.args[0];

		if (args.np != smmu->dev->of_node) {
			of_node_put(args.np);
			continue;
		}

		of_node_put(args.np);

		tegra_smmu_disable(smmu, swgroup, as->id);
		tegra_smmu_as_unprepare(smmu, as);
		index++;
	}
}