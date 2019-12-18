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
struct mobiveil_msi {int /*<<< orphan*/  dev_domain; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  num_of_vectors; int /*<<< orphan*/  lock; } ;
struct mobiveil_pcie {struct mobiveil_msi msi; TYPE_1__* pdev; } ;
struct fwnode_handle {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mobiveil_pcie*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mobiveil_msi_domain_info ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct fwnode_handle* of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mobiveil_allocate_msi_domains(struct mobiveil_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	struct fwnode_handle *fwnode = of_node_to_fwnode(dev->of_node);
	struct mobiveil_msi *msi = &pcie->msi;

	mutex_init(&pcie->msi.lock);
	msi->dev_domain = irq_domain_add_linear(NULL, msi->num_of_vectors,
						&msi_domain_ops, pcie);
	if (!msi->dev_domain) {
		dev_err(dev, "failed to create IRQ domain\n");
		return -ENOMEM;
	}

	msi->msi_domain = pci_msi_create_irq_domain(fwnode,
						    &mobiveil_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain) {
		dev_err(dev, "failed to create MSI domain\n");
		irq_domain_remove(msi->dev_domain);
		return -ENOMEM;
	}

	return 0;
}