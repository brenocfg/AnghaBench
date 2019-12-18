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

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CORE_PCIEXP_CAP ; 
 int /*<<< orphan*/  PCIE_ISR0_MASK_REG ; 
 int /*<<< orphan*/  PCIE_ISR0_REG ; 
#define  PCI_EXP_DEVCTL 131 
#define  PCI_EXP_LNKCTL 130 
#define  PCI_EXP_RTCTL 129 
 int PCI_EXP_RTCTL_PMEIE ; 
#define  PCI_EXP_RTSTA 128 
 int PCI_EXP_RTSTA_PME ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
advk_pci_bridge_emul_pcie_conf_write(struct pci_bridge_emul *bridge,
				     int reg, u32 old, u32 new, u32 mask)
{
	struct advk_pcie *pcie = bridge->data;

	switch (reg) {
	case PCI_EXP_DEVCTL:
	case PCI_EXP_LNKCTL:
		advk_writel(pcie, new, PCIE_CORE_PCIEXP_CAP + reg);
		break;

	case PCI_EXP_RTCTL:
		new = (new & PCI_EXP_RTCTL_PMEIE) << 3;
		advk_writel(pcie, new, PCIE_ISR0_MASK_REG);
		break;

	case PCI_EXP_RTSTA:
		new = (new & PCI_EXP_RTSTA_PME) >> 9;
		advk_writel(pcie, new, PCIE_ISR0_REG);
		break;

	default:
		break;
	}
}