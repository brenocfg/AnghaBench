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
struct pci_dev {int dummy; } ;
struct page {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_map_page (struct pci_dev*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qib_map_page(struct pci_dev *hwdev, struct page *page, dma_addr_t *daddr)
{
	dma_addr_t phys;

	phys = pci_map_page(hwdev, page, 0, PAGE_SIZE, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(hwdev, phys))
		return -ENOMEM;

	if (!phys) {
		pci_unmap_page(hwdev, phys, PAGE_SIZE, PCI_DMA_FROMDEVICE);
		phys = pci_map_page(hwdev, page, 0, PAGE_SIZE,
				    PCI_DMA_FROMDEVICE);
		if (pci_dma_mapping_error(hwdev, phys))
			return -ENOMEM;
		/*
		 * FIXME: If we get 0 again, we should keep this page,
		 * map another, then free the 0 page.
		 */
	}
	*daddr = phys;
	return 0;
}