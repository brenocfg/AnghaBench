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
struct dw_pcie {scalar_t__ dbi_base; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int PORT_LOGIC_MSIX_DOORBELL ; 
 int dw_pcie_write (scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

__attribute__((used)) static int tegra_pcie_dw_wr_own_conf(struct pcie_port *pp, int where, int size,
				     u32 val)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);

	/*
	 * This is an endpoint mode specific register happen to appear even
	 * when controller is operating in root port mode and system hangs
	 * when it is accessed with link being in ASPM-L1 state.
	 * So skip accessing it altogether
	 */
	if (where == PORT_LOGIC_MSIX_DOORBELL)
		return PCIBIOS_SUCCESSFUL;

	return dw_pcie_write(pci->dbi_base + where, size, val);
}