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
struct rcar_msi {int /*<<< orphan*/  pages; } ;
struct rcar_pcie {struct rcar_msi msi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEMSIALR ; 
 int /*<<< orphan*/  PCIEMSIIER ; 
 int /*<<< orphan*/  free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pcie_unmap_msi (struct rcar_pcie*) ; 

__attribute__((used)) static void rcar_pcie_teardown_msi(struct rcar_pcie *pcie)
{
	struct rcar_msi *msi = &pcie->msi;

	/* Disable all MSI interrupts */
	rcar_pci_write_reg(pcie, 0, PCIEMSIIER);

	/* Disable address decoding of the MSI interrupt, MSIFE */
	rcar_pci_write_reg(pcie, 0, PCIEMSIALR);

	free_pages(msi->pages, 0);

	rcar_pcie_unmap_msi(pcie);
}