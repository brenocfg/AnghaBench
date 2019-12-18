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
typedef  int /*<<< orphan*/  pci_bridge_emul_read_status_t ;

/* Variables and functions */
 int const PCIE_CAP_PCIEXP ; 
 int const PCIE_RC_RTSTA ; 
 int /*<<< orphan*/  PCI_BRIDGE_EMUL_HANDLED ; 
 int /*<<< orphan*/  PCI_BRIDGE_EMUL_NOT_HANDLED ; 
#define  PCI_EXP_DEVCAP 133 
#define  PCI_EXP_DEVCTL 132 
 int PCI_EXP_DEVCTL_CERE ; 
 int PCI_EXP_DEVCTL_FERE ; 
 int PCI_EXP_DEVCTL_NFERE ; 
 int PCI_EXP_DEVCTL_URRE ; 
#define  PCI_EXP_LNKCAP 131 
 int PCI_EXP_LNKCAP_CLKPM ; 
#define  PCI_EXP_LNKCTL 130 
#define  PCI_EXP_RTSTA 129 
#define  PCI_EXP_SLTCTL 128 
 int PCI_EXP_SLTSTA_PDS ; 
 int mvebu_readl (struct mvebu_pcie_port*,int const) ; 

__attribute__((used)) static pci_bridge_emul_read_status_t
mvebu_pci_bridge_emul_pcie_conf_read(struct pci_bridge_emul *bridge,
				     int reg, u32 *value)
{
	struct mvebu_pcie_port *port = bridge->data;

	switch (reg) {
	case PCI_EXP_DEVCAP:
		*value = mvebu_readl(port, PCIE_CAP_PCIEXP + PCI_EXP_DEVCAP);
		break;

	case PCI_EXP_DEVCTL:
		*value = mvebu_readl(port, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTL) &
				 ~(PCI_EXP_DEVCTL_URRE | PCI_EXP_DEVCTL_FERE |
				   PCI_EXP_DEVCTL_NFERE | PCI_EXP_DEVCTL_CERE);
		break;

	case PCI_EXP_LNKCAP:
		/*
		 * PCIe requires the clock power management capability to be
		 * hard-wired to zero for downstream ports
		 */
		*value = mvebu_readl(port, PCIE_CAP_PCIEXP + PCI_EXP_LNKCAP) &
			 ~PCI_EXP_LNKCAP_CLKPM;
		break;

	case PCI_EXP_LNKCTL:
		*value = mvebu_readl(port, PCIE_CAP_PCIEXP + PCI_EXP_LNKCTL);
		break;

	case PCI_EXP_SLTCTL:
		*value = PCI_EXP_SLTSTA_PDS << 16;
		break;

	case PCI_EXP_RTSTA:
		*value = mvebu_readl(port, PCIE_RC_RTSTA);
		break;

	default:
		return PCI_BRIDGE_EMUL_NOT_HANDLED;
	}

	return PCI_BRIDGE_EMUL_HANDLED;
}