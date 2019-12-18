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
typedef  size_t u16 ;
struct ice_rx_buf {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  page; int /*<<< orphan*/  dma; } ;
struct ice_ring {size_t next_to_alloc; size_t count; struct ice_rx_buf* rx_buf; } ;

/* Variables and functions */

__attribute__((used)) static void
ice_reuse_rx_page(struct ice_ring *rx_ring, struct ice_rx_buf *old_buf)
{
	u16 nta = rx_ring->next_to_alloc;
	struct ice_rx_buf *new_buf;

	new_buf = &rx_ring->rx_buf[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member individually to avoid possible store
	 * forwarding stalls and unnecessary copy of skb.
	 */
	new_buf->dma = old_buf->dma;
	new_buf->page = old_buf->page;
	new_buf->page_offset = old_buf->page_offset;
	new_buf->pagecnt_bias = old_buf->pagecnt_bias;
}