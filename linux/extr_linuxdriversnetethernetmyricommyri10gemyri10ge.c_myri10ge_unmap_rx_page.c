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
struct myri10ge_rx_buffer_state {int page_offset; } ;

/* Variables and functions */
 int MYRI10GE_ALLOC_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  bus ; 
 int dma_unmap_addr (struct myri10ge_rx_buffer_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
myri10ge_unmap_rx_page(struct pci_dev *pdev,
		       struct myri10ge_rx_buffer_state *info, int bytes)
{
	/* unmap the recvd page if we're the only or last user of it */
	if (bytes >= MYRI10GE_ALLOC_SIZE / 2 ||
	    (info->page_offset + 2 * bytes) > MYRI10GE_ALLOC_SIZE) {
		pci_unmap_page(pdev, (dma_unmap_addr(info, bus)
				      & ~(MYRI10GE_ALLOC_SIZE - 1)),
			       MYRI10GE_ALLOC_SIZE, PCI_DMA_FROMDEVICE);
	}
}