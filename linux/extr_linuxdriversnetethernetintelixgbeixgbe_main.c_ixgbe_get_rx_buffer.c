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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct sk_buff {int dummy; } ;
struct ixgbe_rx_buffer {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; struct sk_buff* skb; int /*<<< orphan*/  page; } ;
struct ixgbe_ring {size_t next_to_clean; int /*<<< orphan*/  dev; struct ixgbe_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_EOP ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_dma_sync_frag (struct ixgbe_ring*,struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ixgbe_rx_buffer *ixgbe_get_rx_buffer(struct ixgbe_ring *rx_ring,
						   union ixgbe_adv_rx_desc *rx_desc,
						   struct sk_buff **skb,
						   const unsigned int size)
{
	struct ixgbe_rx_buffer *rx_buffer;

	rx_buffer = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
	prefetchw(rx_buffer->page);
	*skb = rx_buffer->skb;

	/* Delay unmapping of the first packet. It carries the header
	 * information, HW may still access the header after the writeback.
	 * Only unmap it when EOP is reached
	 */
	if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)) {
		if (!*skb)
			goto skip_sync;
	} else {
		if (*skb)
			ixgbe_dma_sync_frag(rx_ring, *skb);
	}

	/* we are reusing so sync this buffer for CPU use */
	dma_sync_single_range_for_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);
skip_sync:
	rx_buffer->pagecnt_bias--;

	return rx_buffer;
}