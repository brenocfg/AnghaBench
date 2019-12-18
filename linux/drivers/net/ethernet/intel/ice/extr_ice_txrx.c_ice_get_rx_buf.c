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
struct sk_buff {int dummy; } ;
struct ice_rx_buf {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; struct sk_buff* skb; int /*<<< orphan*/  page; } ;
struct ice_ring {size_t next_to_clean; int /*<<< orphan*/  dev; struct ice_rx_buf* rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ice_rx_buf *
ice_get_rx_buf(struct ice_ring *rx_ring, struct sk_buff **skb,
	       const unsigned int size)
{
	struct ice_rx_buf *rx_buf;

	rx_buf = &rx_ring->rx_buf[rx_ring->next_to_clean];
	prefetchw(rx_buf->page);
	*skb = rx_buf->skb;

	if (!size)
		return rx_buf;
	/* we are reusing so sync this buffer for CPU use */
	dma_sync_single_range_for_cpu(rx_ring->dev, rx_buf->dma,
				      rx_buf->page_offset, size,
				      DMA_FROM_DEVICE);

	/* We have pulled a buffer for use, so decrement pagecnt_bias */
	rx_buf->pagecnt_bias--;

	return rx_buf;
}