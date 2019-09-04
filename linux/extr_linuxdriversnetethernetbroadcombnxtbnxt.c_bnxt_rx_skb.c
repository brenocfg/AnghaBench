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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct bnxt_rx_ring_info {int /*<<< orphan*/  rx_prod; } ;
struct bnxt {int /*<<< orphan*/  rx_offset; int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int bnxt_alloc_rx_data (struct bnxt*,struct bnxt_rx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_reuse_rx_data (struct bnxt_rx_ring_info*,int /*<<< orphan*/ ,void*) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *bnxt_rx_skb(struct bnxt *bp,
				   struct bnxt_rx_ring_info *rxr, u16 cons,
				   void *data, u8 *data_ptr,
				   dma_addr_t dma_addr,
				   unsigned int offset_and_len)
{
	u16 prod = rxr->rx_prod;
	struct sk_buff *skb;
	int err;

	err = bnxt_alloc_rx_data(bp, rxr, prod, GFP_ATOMIC);
	if (unlikely(err)) {
		bnxt_reuse_rx_data(rxr, cons, data);
		return NULL;
	}

	skb = build_skb(data, 0);
	dma_unmap_single_attrs(&bp->pdev->dev, dma_addr, bp->rx_buf_use_size,
			       bp->rx_dir, DMA_ATTR_WEAK_ORDERING);
	if (!skb) {
		kfree(data);
		return NULL;
	}

	skb_reserve(skb, bp->rx_offset);
	skb_put(skb, offset_and_len & 0xffff);
	return skb;
}