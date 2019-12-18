#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rx_ring_info {int /*<<< orphan*/ * frag_addr; int /*<<< orphan*/  data_addr; struct sk_buff* skb; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  data_size ; 
 int /*<<< orphan*/  dma_unmap_len (struct rx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void sky2_rx_unmap_skb(struct pci_dev *pdev, struct rx_ring_info *re)
{
	struct sk_buff *skb = re->skb;
	int i;

	pci_unmap_single(pdev, re->data_addr, dma_unmap_len(re, data_size),
			 PCI_DMA_FROMDEVICE);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
		pci_unmap_page(pdev, re->frag_addr[i],
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       PCI_DMA_FROMDEVICE);
}