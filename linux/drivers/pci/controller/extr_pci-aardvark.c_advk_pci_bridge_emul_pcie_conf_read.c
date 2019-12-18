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
struct pci_bridge_emul {struct advk_pcie* data; } ;
struct advk_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  pci_bridge_emul_read_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CORE_PCIEXP_CAP ; 
 int /*<<< orphan*/  PCIE_ISR0_MASK_REG ; 
 int /*<<< orphan*/  PCIE_ISR0_REG ; 
 int /*<<< orphan*/  PCIE_MSG_LOG_REG ; 
 int PCIE_MSG_PM_PME_MASK ; 
 int /*<<< orphan*/  PCI_BRIDGE_EMUL_HANDLED ; 
 int /*<<< orphan*/  PCI_BRIDGE_EMUL_NOT_HANDLED ; 
#define  PCI_CAP_LIST_ID 135 
#define  PCI_EXP_DEVCAP 134 
#define  PCI_EXP_DEVCTL 133 
#define  PCI_EXP_LNKCAP 132 
#define  PCI_EXP_LNKCTL 131 
#define  PCI_EXP_RTCTL 130 
 int PCI_EXP_RTCTL_PMEIE ; 
#define  PCI_EXP_RTSTA 129 
#define  PCI_EXP_SLTCTL 128 
 int PCI_EXP_SLTSTA_PDS ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_bridge_emul_read_status_t
advk_pci_bridge_emul_pcie_conf_read(struct pci_bridge_emul *bridge,
				    int reg, u32 *value)
{
	struct advk_pcie *pcie = bridge->data;


	switch (reg) {
	case PCI_EXP_SLTCTL:
		*value = PCI_EXP_SLTSTA_PDS << 16;
		return PCI_BRIDGE_EMUL_HANDLED;

	case PCI_EXP_RTCTL: {
		u32 val = advk_readl(pcie, PCIE_ISR0_MASK_REG);
		*value = (val & PCIE_MSG_PM_PME_MASK) ? PCI_EXP_RTCTL_PMEIE : 0;
		return PCI_BRIDGE_EMUL_HANDLED;
	}

	case PCI_EXP_RTSTA: {
		u32 isr0 = advk_readl(pcie, PCIE_ISR0_REG);
		u32 msglog = advk_readl(pcie, PCIE_MSG_LOG_REG);
		*value = (isr0 & PCIE_MSG_PM_PME_MASK) << 16 | (msglog >> 16);
		return PCI_BRIDGE_EMUL_HANDLED;
	}

	case PCI_CAP_LIST_ID:
	case PCI_EXP_DEVCAP:
	case PCI_EXP_DEVCTL:
	case PCI_EXP_LNKCAP:
	case PCI_EXP_LNKCTL:
		*value = advk_readl(pcie, PCIE_CORE_PCIEXP_CAP + reg);
		return PCI_BRIDGE_EMUL_HANDLED;
	default:
		return PCI_BRIDGE_EMUL_NOT_HANDLED;
	}

}