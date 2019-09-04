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
typedef  size_t u32 ;
struct typhoon {int /*<<< orphan*/  pdev; struct rxbuff_ent* rxbuffers; } ;
struct rxbuff_ent {int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 size_t RXENT_ENTRIES ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
typhoon_free_rx_rings(struct typhoon *tp)
{
	u32 i;

	for(i = 0; i < RXENT_ENTRIES; i++) {
		struct rxbuff_ent *rxb = &tp->rxbuffers[i];
		if(rxb->skb) {
			pci_unmap_single(tp->pdev, rxb->dma_addr, PKT_BUF_SZ,
				       PCI_DMA_FROMDEVICE);
			dev_kfree_skb(rxb->skb);
			rxb->skb = NULL;
		}
	}
}