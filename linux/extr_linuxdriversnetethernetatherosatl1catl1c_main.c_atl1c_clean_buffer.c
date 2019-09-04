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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct atl1c_buffer {int flags; int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ATL1C_BUFFER_FREE ; 
 int ATL1C_PCIMAP_FROMDEVICE ; 
 int ATL1C_PCIMAP_PAGE ; 
 int ATL1C_PCIMAP_SINGLE ; 
 int /*<<< orphan*/  ATL1C_SET_BUFFER_STATE (struct atl1c_buffer*,int) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atl1c_clean_buffer(struct pci_dev *pdev,
				struct atl1c_buffer *buffer_info)
{
	u16 pci_driection;
	if (buffer_info->flags & ATL1C_BUFFER_FREE)
		return;
	if (buffer_info->dma) {
		if (buffer_info->flags & ATL1C_PCIMAP_FROMDEVICE)
			pci_driection = PCI_DMA_FROMDEVICE;
		else
			pci_driection = PCI_DMA_TODEVICE;

		if (buffer_info->flags & ATL1C_PCIMAP_SINGLE)
			pci_unmap_single(pdev, buffer_info->dma,
					buffer_info->length, pci_driection);
		else if (buffer_info->flags & ATL1C_PCIMAP_PAGE)
			pci_unmap_page(pdev, buffer_info->dma,
					buffer_info->length, pci_driection);
	}
	if (buffer_info->skb)
		dev_consume_skb_any(buffer_info->skb);
	buffer_info->dma = 0;
	buffer_info->skb = NULL;
	ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_FREE);
}