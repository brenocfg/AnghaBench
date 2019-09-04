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
struct pcidev_info {scalar_t__ pdi_pcibus_info; } ;
struct pcibus_info {int dummy; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ ATE_SWAP_OFF (int /*<<< orphan*/ ) ; 
 int IOPG (scalar_t__) ; 
 scalar_t__ IS_PCI32_MAPPED (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI32_MAPPED_BASE ; 
 struct pcidev_info* SN_PCIDEV_INFO (struct pci_dev*) ; 
 int /*<<< orphan*/  pcibr_ate_free (struct pcibus_info*,int) ; 

void
pcibr_dma_unmap(struct pci_dev *hwdev, dma_addr_t dma_handle, int direction)
{
	struct pcidev_info *pcidev_info = SN_PCIDEV_INFO(hwdev);
	struct pcibus_info *pcibus_info =
	    (struct pcibus_info *)pcidev_info->pdi_pcibus_info;

	if (IS_PCI32_MAPPED(dma_handle)) {
		int ate_index;

		ate_index =
		    IOPG((ATE_SWAP_OFF(dma_handle) - PCI32_MAPPED_BASE));
		pcibr_ate_free(pcibus_info, ate_index);
	}
}