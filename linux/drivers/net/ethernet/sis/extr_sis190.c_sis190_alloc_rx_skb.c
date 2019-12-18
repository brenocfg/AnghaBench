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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct sis190_private {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  dev; } ;
struct RxDesc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis190_make_unusable_by_asic (struct RxDesc*) ; 
 int /*<<< orphan*/  sis190_map_to_asic (struct RxDesc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *sis190_alloc_rx_skb(struct sis190_private *tp,
					   struct RxDesc *desc)
{
	u32 rx_buf_sz = tp->rx_buf_sz;
	struct sk_buff *skb;
	dma_addr_t mapping;

	skb = netdev_alloc_skb(tp->dev, rx_buf_sz);
	if (unlikely(!skb))
		goto skb_alloc_failed;
	mapping = pci_map_single(tp->pci_dev, skb->data, tp->rx_buf_sz,
			PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(tp->pci_dev, mapping))
		goto out;
	sis190_map_to_asic(desc, mapping, rx_buf_sz);

	return skb;

out:
	dev_kfree_skb_any(skb);
skb_alloc_failed:
	sis190_make_unusable_by_asic(desc);
	return NULL;
}