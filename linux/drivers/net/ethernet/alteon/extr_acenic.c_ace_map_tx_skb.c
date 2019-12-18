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
typedef  int u32 ;
struct tx_ring_info {struct sk_buff* skb; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ace_private {TYPE_1__* skb; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct tx_ring_info* tx_skbuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct tx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct tx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t
ace_map_tx_skb(struct ace_private *ap, struct sk_buff *skb,
	       struct sk_buff *tail, u32 idx)
{
	dma_addr_t mapping;
	struct tx_ring_info *info;

	mapping = pci_map_page(ap->pdev, virt_to_page(skb->data),
			       offset_in_page(skb->data),
			       skb->len, PCI_DMA_TODEVICE);

	info = ap->skb->tx_skbuff + idx;
	info->skb = tail;
	dma_unmap_addr_set(info, mapping, mapping);
	dma_unmap_len_set(info, maplen, skb->len);
	return mapping;
}