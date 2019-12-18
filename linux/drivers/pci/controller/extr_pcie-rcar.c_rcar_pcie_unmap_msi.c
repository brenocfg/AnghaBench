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
struct rcar_msi {int /*<<< orphan*/  domain; } ;
struct rcar_pcie {struct rcar_msi msi; } ;

/* Variables and functions */
 int INT_PCI_MSI_NR ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_pcie_unmap_msi(struct rcar_pcie *pcie)
{
	struct rcar_msi *msi = &pcie->msi;
	int i, irq;

	for (i = 0; i < INT_PCI_MSI_NR; i++) {
		irq = irq_find_mapping(msi->domain, i);
		if (irq > 0)
			irq_dispose_mapping(irq);
	}

	irq_domain_remove(msi->domain);
}