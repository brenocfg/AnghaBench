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
struct dw_pcie {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct armada8k_pcie {int /*<<< orphan*/  phy_count; int /*<<< orphan*/ ** phy; struct dw_pcie* pci; } ;

/* Variables and functions */
 int ARMADA8K_PCIE_MAX_LANES ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int armada8k_pcie_enable_phys (struct armada8k_pcie*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_of_phy_get_by_index (struct device*,struct device_node*,int) ; 

__attribute__((used)) static int armada8k_pcie_setup_phys(struct armada8k_pcie *pcie)
{
	struct dw_pcie *pci = pcie->pci;
	struct device *dev = pci->dev;
	struct device_node *node = dev->of_node;
	int ret = 0;
	int i;

	for (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) {
		pcie->phy[i] = devm_of_phy_get_by_index(dev, node, i);
		if (IS_ERR(pcie->phy[i])) {
			if (PTR_ERR(pcie->phy[i]) != -ENODEV)
				return PTR_ERR(pcie->phy[i]);

			pcie->phy[i] = NULL;
			continue;
		}

		pcie->phy_count++;
	}

	/* Old bindings miss the PHY handle, so just warn if there is no PHY */
	if (!pcie->phy_count)
		dev_warn(dev, "No available PHY\n");

	ret = armada8k_pcie_enable_phys(pcie);
	if (ret)
		dev_err(dev, "Failed to initialize PHY(s) (%d)\n", ret);

	return ret;
}