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
struct genwqe_dev {struct pci_dev* pci_dev; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genwqe_unmap_pages(struct genwqe_dev *cd, dma_addr_t *dma_list,
			      int num_pages)
{
	int i;
	struct pci_dev *pci_dev = cd->pci_dev;

	for (i = 0; (i < num_pages) && (dma_list[i] != 0x0); i++) {
		pci_unmap_page(pci_dev, dma_list[i],
			       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
		dma_list[i] = 0x0;
	}
}