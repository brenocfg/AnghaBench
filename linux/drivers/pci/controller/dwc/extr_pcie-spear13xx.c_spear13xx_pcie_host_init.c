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
struct spear13xx_pcie {int dummy; } ;
struct pcie_port {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spear13xx_pcie_enable_interrupts (struct spear13xx_pcie*) ; 
 int /*<<< orphan*/  spear13xx_pcie_establish_link (struct spear13xx_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct spear13xx_pcie* to_spear13xx_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int spear13xx_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct spear13xx_pcie *spear13xx_pcie = to_spear13xx_pcie(pci);

	spear13xx_pcie_establish_link(spear13xx_pcie);
	spear13xx_pcie_enable_interrupts(spear13xx_pcie);

	return 0;
}