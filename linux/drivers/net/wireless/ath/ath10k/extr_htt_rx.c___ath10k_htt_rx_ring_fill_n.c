#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_5__ {void* flags; } ;
struct htt_rx_desc {TYPE_1__ attention; } ;
struct ath10k_skb_rxcb {int /*<<< orphan*/  hlist; int /*<<< orphan*/  paddr; } ;
struct TYPE_7__ {void** vaddr; } ;
struct TYPE_8__ {int size_mask; TYPE_3__ alloc_idx; int /*<<< orphan*/  skb_table; scalar_t__ in_ord_rx; int /*<<< orphan*/  fill_cnt; struct sk_buff** netbufs_ring; } ;
struct ath10k_htt {TYPE_4__ rx_ring; TYPE_2__* ar; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ath10k_skb_rxcb* ATH10K_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ HTT_RX_BUF_SIZE ; 
 scalar_t__ HTT_RX_DESC_ALIGN ; 
 int HTT_RX_RING_FILL_LEVEL ; 
 int HTT_RX_RING_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 scalar_t__ PTR_ALIGN (scalar_t__,scalar_t__) ; 
 void* __cpu_to_le32 (int) ; 
 int __le32_to_cpu (void*) ; 
 int /*<<< orphan*/  ath10k_htt_set_paddrs_ring (struct ath10k_htt*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ath10k_htt_rx_ring_fill_n(struct ath10k_htt *htt, int num)
{
	struct htt_rx_desc *rx_desc;
	struct ath10k_skb_rxcb *rxcb;
	struct sk_buff *skb;
	dma_addr_t paddr;
	int ret = 0, idx;

	/* The Full Rx Reorder firmware has no way of telling the host
	 * implicitly when it copied HTT Rx Ring buffers to MAC Rx Ring.
	 * To keep things simple make sure ring is always half empty. This
	 * guarantees there'll be no replenishment overruns possible.
	 */
	BUILD_BUG_ON(HTT_RX_RING_FILL_LEVEL >= HTT_RX_RING_SIZE / 2);

	idx = __le32_to_cpu(*htt->rx_ring.alloc_idx.vaddr);
	while (num > 0) {
		skb = dev_alloc_skb(HTT_RX_BUF_SIZE + HTT_RX_DESC_ALIGN);
		if (!skb) {
			ret = -ENOMEM;
			goto fail;
		}

		if (!IS_ALIGNED((unsigned long)skb->data, HTT_RX_DESC_ALIGN))
			skb_pull(skb,
				 PTR_ALIGN(skb->data, HTT_RX_DESC_ALIGN) -
				 skb->data);

		/* Clear rx_desc attention word before posting to Rx ring */
		rx_desc = (struct htt_rx_desc *)skb->data;
		rx_desc->attention.flags = __cpu_to_le32(0);

		paddr = dma_map_single(htt->ar->dev, skb->data,
				       skb->len + skb_tailroom(skb),
				       DMA_FROM_DEVICE);

		if (unlikely(dma_mapping_error(htt->ar->dev, paddr))) {
			dev_kfree_skb_any(skb);
			ret = -ENOMEM;
			goto fail;
		}

		rxcb = ATH10K_SKB_RXCB(skb);
		rxcb->paddr = paddr;
		htt->rx_ring.netbufs_ring[idx] = skb;
		ath10k_htt_set_paddrs_ring(htt, paddr, idx);
		htt->rx_ring.fill_cnt++;

		if (htt->rx_ring.in_ord_rx) {
			hash_add(htt->rx_ring.skb_table,
				 &ATH10K_SKB_RXCB(skb)->hlist,
				 paddr);
		}

		num--;
		idx++;
		idx &= htt->rx_ring.size_mask;
	}

fail:
	/*
	 * Make sure the rx buffer is updated before available buffer
	 * index to avoid any potential rx ring corruption.
	 */
	mb();
	*htt->rx_ring.alloc_idx.vaddr = __cpu_to_le32(idx);
	return ret;
}