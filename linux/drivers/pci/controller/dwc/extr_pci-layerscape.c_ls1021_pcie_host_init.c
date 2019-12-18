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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {int dummy; } ;
struct ls_pcie {int /*<<< orphan*/  index; int /*<<< orphan*/ * scfg; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ls_pcie_host_init (struct pcie_port*) ; 
 scalar_t__ of_property_read_u32_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct ls_pcie* to_ls_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ls1021_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct ls_pcie *pcie = to_ls_pcie(pci);
	struct device *dev = pci->dev;
	u32 index[2];
	int ret;

	pcie->scfg = syscon_regmap_lookup_by_phandle(dev->of_node,
						     "fsl,pcie-scfg");
	if (IS_ERR(pcie->scfg)) {
		ret = PTR_ERR(pcie->scfg);
		dev_err(dev, "No syscfg phandle specified\n");
		pcie->scfg = NULL;
		return ret;
	}

	if (of_property_read_u32_array(dev->of_node,
				       "fsl,pcie-scfg", index, 2)) {
		pcie->scfg = NULL;
		return -EINVAL;
	}
	pcie->index = index[1];

	return ls_pcie_host_init(pp);
}