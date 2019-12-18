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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/  np; int /*<<< orphan*/  args; } ;
struct of_pci_iommu_alias_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  np; } ;

/* Variables and functions */
 int ENODEV ; 
 int NO_IOMMU ; 
 int of_iommu_xlate (int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int of_map_rid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_pci_iommu_init(struct pci_dev *pdev, u16 alias, void *data)
{
	struct of_pci_iommu_alias_info *info = data;
	struct of_phandle_args iommu_spec = { .args_count = 1 };
	int err;

	err = of_map_rid(info->np, alias, "iommu-map", "iommu-map-mask",
			 &iommu_spec.np, iommu_spec.args);
	if (err)
		return err == -ENODEV ? NO_IOMMU : err;

	err = of_iommu_xlate(info->dev, &iommu_spec);
	of_node_put(iommu_spec.np);
	return err;
}