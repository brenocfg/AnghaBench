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
struct skge_element {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int BMU_STF ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dma_unmap_addr (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void skge_tx_unmap(struct pci_dev *pdev, struct skge_element *e,
				 u32 control)
{
	/* skb header vs. fragment */
	if (control & BMU_STF)
		pci_unmap_single(pdev, dma_unmap_addr(e, mapaddr),
				 dma_unmap_len(e, maplen),
				 PCI_DMA_TODEVICE);
	else
		pci_unmap_page(pdev, dma_unmap_addr(e, mapaddr),
			       dma_unmap_len(e, maplen),
			       PCI_DMA_TODEVICE);
}