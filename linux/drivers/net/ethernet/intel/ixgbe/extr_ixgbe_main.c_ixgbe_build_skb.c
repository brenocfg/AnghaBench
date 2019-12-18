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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct xdp_buff {unsigned int data; unsigned int data_meta; int data_end; int data_hard_start; } ;
struct skb_shared_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ixgbe_rx_buffer {unsigned int page_offset; int /*<<< orphan*/  dma; } ;
struct ixgbe_ring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 TYPE_1__* IXGBE_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_EOP ; 
 unsigned int L1_CACHE_BYTES ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 struct sk_buff* build_skb (int,unsigned int) ; 
 int ixgbe_rx_pg_size (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (unsigned int) ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ixgbe_build_skb(struct ixgbe_ring *rx_ring,
				       struct ixgbe_rx_buffer *rx_buffer,
				       struct xdp_buff *xdp,
				       union ixgbe_adv_rx_desc *rx_desc)
{
	unsigned int metasize = xdp->data - xdp->data_meta;
#if (PAGE_SIZE < 8192)
	unsigned int truesize = ixgbe_rx_pg_size(rx_ring) / 2;
#else
	unsigned int truesize = SKB_DATA_ALIGN(sizeof(struct skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#endif
	struct sk_buff *skb;

	/* Prefetch first cache line of first page. If xdp->data_meta
	 * is unused, this points extactly as xdp->data, otherwise we
	 * likely have a consumer accessing first few bytes of meta
	 * data, and then actual data.
	 */
	prefetch(xdp->data_meta);
#if L1_CACHE_BYTES < 128
	prefetch(xdp->data_meta + L1_CACHE_BYTES);
#endif

	/* build an skb to around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	if (unlikely(!skb))
		return NULL;

	/* update pointers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);
	if (metasize)
		skb_metadata_set(skb, metasize);

	/* record DMA address if this is the start of a chain of buffers */
	if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP))
		IXGBE_CB(skb)->dma = rx_buffer->dma;

	/* update buffer offset */
#if (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#else
	rx_buffer->page_offset += truesize;
#endif

	return skb;
}