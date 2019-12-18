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
struct tegra_msi {scalar_t__ irq; int /*<<< orphan*/  domain; int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct tegra_pcie {int /*<<< orphan*/  dev; struct tegra_msi msi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NO_KERNEL_MAPPING ; 
 unsigned int INT_PCI_MSI_NR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct tegra_pcie*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void tegra_pcie_msi_teardown(struct tegra_pcie *pcie)
{
	struct tegra_msi *msi = &pcie->msi;
	unsigned int i, irq;

	dma_free_attrs(pcie->dev, PAGE_SIZE, msi->virt, msi->phys,
		       DMA_ATTR_NO_KERNEL_MAPPING);

	if (msi->irq > 0)
		free_irq(msi->irq, pcie);

	for (i = 0; i < INT_PCI_MSI_NR; i++) {
		irq = irq_find_mapping(msi->domain, i);
		if (irq > 0)
			irq_dispose_mapping(irq);
	}

	irq_domain_remove(msi->domain);
}