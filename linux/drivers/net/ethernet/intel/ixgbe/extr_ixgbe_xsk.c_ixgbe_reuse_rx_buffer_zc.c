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
typedef  scalar_t__ u16 ;
struct ixgbe_rx_buffer {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * addr; int /*<<< orphan*/  handle; int /*<<< orphan*/  dma; } ;
struct ixgbe_ring {scalar_t__ next_to_alloc; scalar_t__ count; struct ixgbe_rx_buffer* rx_buffer_info; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbe_reuse_rx_buffer_zc(struct ixgbe_ring *rx_ring,
				     struct ixgbe_rx_buffer *obi)
{
	u16 nta = rx_ring->next_to_alloc;
	struct ixgbe_rx_buffer *nbi;

	nbi = &rx_ring->rx_buffer_info[rx_ring->next_to_alloc];
	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	nbi->dma = obi->dma;
	nbi->addr = obi->addr;
	nbi->handle = obi->handle;

	obi->addr = NULL;
	obi->skb = NULL;
}