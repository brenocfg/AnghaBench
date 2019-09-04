#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pcidev_info {TYPE_1__* pdi_linux_pcidev; TYPE_2__* pdi_host_pcidev_info; } ;
struct pcibus_info {scalar_t__ pbi_hub_xid; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {scalar_t__ pdi_pcibus_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 scalar_t__ IS_PCIX (struct pcibus_info*) ; 
 scalar_t__ IS_PIC_SOFT (struct pcibus_info*) ; 
 int PCI64_ATTR_PREF ; 
 int PCI64_ATTR_VIRTUAL ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PHYS_TO_DMA (int) ; 
 int PHYS_TO_TIODMA (int) ; 
 int PIC_PCI64_ATTR_TARG_SHFT ; 
 scalar_t__ SN_DMA_ADDRTYPE (int) ; 
 scalar_t__ SN_DMA_ADDR_PHYS ; 
 int SN_DMA_MSI ; 
 int TIOCP_PCI64_CMDTYPE_MEM ; 
 int TIOCP_PCI64_CMDTYPE_MSI ; 

__attribute__((used)) static dma_addr_t
pcibr_dmatrans_direct64(struct pcidev_info * info, u64 paddr,
			u64 dma_attributes, int dma_flags)
{
	struct pcibus_info *pcibus_info = (struct pcibus_info *)
	    ((info->pdi_host_pcidev_info)->pdi_pcibus_info);
	u64 pci_addr;

	/* Translate to Crosstalk View of Physical Address */
	if (SN_DMA_ADDRTYPE(dma_flags) == SN_DMA_ADDR_PHYS)
		pci_addr = IS_PIC_SOFT(pcibus_info) ?
				PHYS_TO_DMA(paddr) :
				PHYS_TO_TIODMA(paddr);
	else
		pci_addr = paddr;
	pci_addr |= dma_attributes;

	/* Handle Bus mode */
	if (IS_PCIX(pcibus_info))
		pci_addr &= ~PCI64_ATTR_PREF;

	/* Handle Bridge Chipset differences */
	if (IS_PIC_SOFT(pcibus_info)) {
		pci_addr |=
		    ((u64) pcibus_info->
		     pbi_hub_xid << PIC_PCI64_ATTR_TARG_SHFT);
	} else
		pci_addr |= (dma_flags & SN_DMA_MSI) ?
				TIOCP_PCI64_CMDTYPE_MSI :
				TIOCP_PCI64_CMDTYPE_MEM;

	/* If PCI mode, func zero uses VCHAN0, every other func uses VCHAN1 */
	if (!IS_PCIX(pcibus_info) && PCI_FUNC(info->pdi_linux_pcidev->devfn))
		pci_addr |= PCI64_ATTR_VIRTUAL;

	return pci_addr;
}