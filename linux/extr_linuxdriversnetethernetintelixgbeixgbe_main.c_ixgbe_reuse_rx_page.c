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
struct ixgbe_rx_buffer {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page_offset; int /*<<< orphan*/  page; int /*<<< orphan*/  dma; } ;
struct ixgbe_ring {size_t next_to_alloc; size_t count; struct ixgbe_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbe_reuse_rx_page(struct ixgbe_ring *rx_ring,
				struct ixgbe_rx_buffer *old_buff)
{
	struct ixgbe_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member individually to avoid possible store
	 * forwarding stalls and unnecessary copy of skb.
	 */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;
}