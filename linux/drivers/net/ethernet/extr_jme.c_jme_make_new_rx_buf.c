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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct jme_ring {struct jme_buffer_info* bufinf; } ;
struct jme_buffer_info {int /*<<< orphan*/  mapping; int /*<<< orphan*/  len; struct sk_buff* skb; } ;
struct jme_adapter {int /*<<< orphan*/  pdev; TYPE_1__* dev; struct jme_ring* rxring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ RX_EXTRA_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jme_make_new_rx_buf(struct jme_adapter *jme, int i)
{
	struct jme_ring *rxring = &(jme->rxring[0]);
	struct jme_buffer_info *rxbi = rxring->bufinf + i;
	struct sk_buff *skb;
	dma_addr_t mapping;

	skb = netdev_alloc_skb(jme->dev,
		jme->dev->mtu + RX_EXTRA_LEN);
	if (unlikely(!skb))
		return -ENOMEM;

	mapping = pci_map_page(jme->pdev, virt_to_page(skb->data),
			       offset_in_page(skb->data), skb_tailroom(skb),
			       PCI_DMA_FROMDEVICE);
	if (unlikely(pci_dma_mapping_error(jme->pdev, mapping))) {
		dev_kfree_skb(skb);
		return -ENOMEM;
	}

	if (likely(rxbi->mapping))
		pci_unmap_page(jme->pdev, rxbi->mapping,
			       rxbi->len, PCI_DMA_FROMDEVICE);

	rxbi->skb = skb;
	rxbi->len = skb_tailroom(skb);
	rxbi->mapping = mapping;
	return 0;
}