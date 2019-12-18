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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pci_epc {int dummy; } ;
struct cdns_pcie {int dummy; } ;
struct cdns_pcie_ep {struct cdns_pcie pcie; } ;

/* Variables and functions */
 scalar_t__ CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET ; 
 scalar_t__ PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_64BIT ; 
 int PCI_MSI_FLAGS_MASKBIT ; 
 int PCI_MSI_FLAGS_QMASK ; 
 int cdns_pcie_ep_fn_readw (struct cdns_pcie*,int,scalar_t__) ; 
 int /*<<< orphan*/  cdns_pcie_ep_fn_writew (struct cdns_pcie*,int,scalar_t__,int) ; 
 struct cdns_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 

__attribute__((used)) static int cdns_pcie_ep_set_msi(struct pci_epc *epc, u8 fn, u8 mmc)
{
	struct cdns_pcie_ep *ep = epc_get_drvdata(epc);
	struct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 flags;

	/*
	 * Set the Multiple Message Capable bitfield into the Message Control
	 * register.
	 */
	flags = cdns_pcie_ep_fn_readw(pcie, fn, cap + PCI_MSI_FLAGS);
	flags = (flags & ~PCI_MSI_FLAGS_QMASK) | (mmc << 1);
	flags |= PCI_MSI_FLAGS_64BIT;
	flags &= ~PCI_MSI_FLAGS_MASKBIT;
	cdns_pcie_ep_fn_writew(pcie, fn, cap + PCI_MSI_FLAGS, flags);

	return 0;
}