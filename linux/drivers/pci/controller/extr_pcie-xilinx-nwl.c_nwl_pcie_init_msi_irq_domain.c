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
struct nwl_msi {int /*<<< orphan*/  dev_domain; int /*<<< orphan*/  msi_domain; } ;
struct nwl_pcie {struct nwl_msi msi; struct device* dev; } ;
struct fwnode_handle {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INT_PCI_MSI_NR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_msi_domain_ops ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nwl_pcie*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nwl_msi_domain_info ; 
 struct fwnode_handle* of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nwl_pcie_init_msi_irq_domain(struct nwl_pcie *pcie)
{
#ifdef CONFIG_PCI_MSI
	struct device *dev = pcie->dev;
	struct fwnode_handle *fwnode = of_node_to_fwnode(dev->of_node);
	struct nwl_msi *msi = &pcie->msi;

	msi->dev_domain = irq_domain_add_linear(NULL, INT_PCI_MSI_NR,
						&dev_msi_domain_ops, pcie);
	if (!msi->dev_domain) {
		dev_err(dev, "failed to create dev IRQ domain\n");
		return -ENOMEM;
	}
	msi->msi_domain = pci_msi_create_irq_domain(fwnode,
						    &nwl_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain) {
		dev_err(dev, "failed to create msi IRQ domain\n");
		irq_domain_remove(msi->dev_domain);
		return -ENOMEM;
	}
#endif
	return 0;
}