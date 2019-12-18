#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sky2_port {TYPE_1__* hw; int /*<<< orphan*/  netdev; } ;
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct rx_ring_info {TYPE_2__* skb; int /*<<< orphan*/  data_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct TYPE_7__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (TYPE_2__*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_copy_tag (struct sk_buff*,TYPE_2__*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clear_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_copy_hash (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static struct sk_buff *receive_copy(struct sky2_port *sky2,
				    const struct rx_ring_info *re,
				    unsigned length)
{
	struct sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(sky2->netdev, length);
	if (likely(skb)) {
		pci_dma_sync_single_for_cpu(sky2->hw->pdev, re->data_addr,
					    length, PCI_DMA_FROMDEVICE);
		skb_copy_from_linear_data(re->skb, skb->data, length);
		skb->ip_summed = re->skb->ip_summed;
		skb->csum = re->skb->csum;
		skb_copy_hash(skb, re->skb);
		__vlan_hwaccel_copy_tag(skb, re->skb);

		pci_dma_sync_single_for_device(sky2->hw->pdev, re->data_addr,
					       length, PCI_DMA_FROMDEVICE);
		__vlan_hwaccel_clear_tag(re->skb);
		skb_clear_hash(re->skb);
		re->skb->ip_summed = CHECKSUM_NONE;
		skb_put(skb, length);
	}
	return skb;
}