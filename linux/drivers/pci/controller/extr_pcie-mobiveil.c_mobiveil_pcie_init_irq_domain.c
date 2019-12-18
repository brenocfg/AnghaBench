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
struct mobiveil_pcie {int /*<<< orphan*/  intx_mask_lock; int /*<<< orphan*/  intx_domain; TYPE_1__* pdev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_NUM_INTX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  intx_domain_ops ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mobiveil_pcie*) ; 
 int mobiveil_allocate_msi_domains (struct mobiveil_pcie*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mobiveil_pcie_init_irq_domain(struct mobiveil_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	struct device_node *node = dev->of_node;
	int ret;

	/* setup INTx */
	pcie->intx_domain = irq_domain_add_linear(node, PCI_NUM_INTX,
						  &intx_domain_ops, pcie);

	if (!pcie->intx_domain) {
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		return -ENOMEM;
	}

	raw_spin_lock_init(&pcie->intx_mask_lock);

	/* setup MSI */
	ret = mobiveil_allocate_msi_domains(pcie);
	if (ret)
		return ret;

	return 0;
}