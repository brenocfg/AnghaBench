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
typedef  int u32 ;
struct pci_bridge_emul {struct mvebu_pcie_port* data; } ;
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
 int const PCIE_CAP_PCIEXP ; 
 int const PCIE_RC_RTSTA ; 
#define  PCI_EXP_DEVCTL 130 
 int PCI_EXP_DEVCTL_CERE ; 
 int PCI_EXP_DEVCTL_FERE ; 
 int PCI_EXP_DEVCTL_NFERE ; 
 int PCI_EXP_DEVCTL_URRE ; 
#define  PCI_EXP_LNKCTL 129 
 int PCI_EXP_LNKCTL_CLKREQ_EN ; 
#define  PCI_EXP_RTSTA 128 
 int /*<<< orphan*/  mvebu_writel (struct mvebu_pcie_port*,int,int const) ; 

__attribute__((used)) static void
mvebu_pci_bridge_emul_pcie_conf_write(struct pci_bridge_emul *bridge,
				      int reg, u32 old, u32 new, u32 mask)
{
	struct mvebu_pcie_port *port = bridge->data;

	switch (reg) {
	case PCI_EXP_DEVCTL:
		/*
		 * Armada370 data says these bits must always
		 * be zero when in root complex mode.
		 */
		new &= ~(PCI_EXP_DEVCTL_URRE | PCI_EXP_DEVCTL_FERE |
			 PCI_EXP_DEVCTL_NFERE | PCI_EXP_DEVCTL_CERE);

		mvebu_writel(port, new, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTL);
		break;

	case PCI_EXP_LNKCTL:
		/*
		 * If we don't support CLKREQ, we must ensure that the
		 * CLKREQ enable bit always reads zero.  Since we haven't
		 * had this capability, and it's dependent on board wiring,
		 * disable it for the time being.
		 */
		new &= ~PCI_EXP_LNKCTL_CLKREQ_EN;

		mvebu_writel(port, new, PCIE_CAP_PCIEXP + PCI_EXP_LNKCTL);
		break;

	case PCI_EXP_RTSTA:
		mvebu_writel(port, new, PCIE_RC_RTSTA);
		break;
	}
}