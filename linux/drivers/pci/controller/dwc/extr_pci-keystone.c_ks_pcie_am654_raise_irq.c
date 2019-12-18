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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct keystone_pcie {int dummy; } ;
struct dw_pcie_ep {int dummy; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;
typedef  enum pci_epc_irq_type { ____Placeholder_pci_epc_irq_type } pci_epc_irq_type ;

/* Variables and functions */
 int EINVAL ; 
#define  PCI_EPC_IRQ_LEGACY 129 
#define  PCI_EPC_IRQ_MSI 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_pcie_ep_raise_msi_irq (struct dw_pcie_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_pcie_am654_raise_legacy_irq (struct keystone_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 
 struct keystone_pcie* to_keystone_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int ks_pcie_am654_raise_irq(struct dw_pcie_ep *ep, u8 func_no,
				   enum pci_epc_irq_type type,
				   u16 interrupt_num)
{
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	switch (type) {
	case PCI_EPC_IRQ_LEGACY:
		ks_pcie_am654_raise_legacy_irq(ks_pcie);
		break;
	case PCI_EPC_IRQ_MSI:
		dw_pcie_ep_raise_msi_irq(ep, func_no, interrupt_num);
		break;
	default:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
		return -EINVAL;
	}

	return 0;
}