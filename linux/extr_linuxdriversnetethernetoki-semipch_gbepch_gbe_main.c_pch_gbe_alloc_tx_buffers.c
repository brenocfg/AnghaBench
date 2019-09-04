#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct pch_gbe_tx_ring {unsigned int count; struct pch_gbe_buffer* buffer_info; } ;
struct pch_gbe_tx_desc {int /*<<< orphan*/  gbec_status; } ;
struct pch_gbe_buffer {struct sk_buff* skb; } ;
struct TYPE_4__ {unsigned int max_frame_size; } ;
struct TYPE_3__ {TYPE_2__ mac; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_INIT16 ; 
 unsigned int NET_IP_ALIGN ; 
 unsigned int PCH_GBE_DMA_ALIGN ; 
 struct pch_gbe_tx_desc* PCH_GBE_TX_DESC (struct pch_gbe_tx_ring,unsigned int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void pch_gbe_alloc_tx_buffers(struct pch_gbe_adapter *adapter,
					struct pch_gbe_tx_ring *tx_ring)
{
	struct pch_gbe_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned int i;
	unsigned int bufsz;
	struct pch_gbe_tx_desc *tx_desc;

	bufsz =
	    adapter->hw.mac.max_frame_size + PCH_GBE_DMA_ALIGN + NET_IP_ALIGN;

	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		skb = netdev_alloc_skb(adapter->netdev, bufsz);
		skb_reserve(skb, PCH_GBE_DMA_ALIGN);
		buffer_info->skb = skb;
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, i);
		tx_desc->gbec_status = (DSC_INIT16);
	}
	return;
}