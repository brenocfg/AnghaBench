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
struct pci_epc {int dummy; } ;
struct cdns_pcie_ep {int dummy; } ;
typedef  enum pci_epc_irq_type { ____Placeholder_pci_epc_irq_type } pci_epc_irq_type ;

/* Variables and functions */
 int EINVAL ; 
#define  PCI_EPC_IRQ_LEGACY 129 
#define  PCI_EPC_IRQ_MSI 128 
 int cdns_pcie_ep_send_legacy_irq (struct cdns_pcie_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cdns_pcie_ep_send_msi_irq (struct cdns_pcie_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdns_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 

__attribute__((used)) static int cdns_pcie_ep_raise_irq(struct pci_epc *epc, u8 fn,
				  enum pci_epc_irq_type type,
				  u16 interrupt_num)
{
	struct cdns_pcie_ep *ep = epc_get_drvdata(epc);

	switch (type) {
	case PCI_EPC_IRQ_LEGACY:
		return cdns_pcie_ep_send_legacy_irq(ep, fn, 0);

	case PCI_EPC_IRQ_MSI:
		return cdns_pcie_ep_send_msi_irq(ep, fn, interrupt_num);

	default:
		break;
	}

	return -EINVAL;
}