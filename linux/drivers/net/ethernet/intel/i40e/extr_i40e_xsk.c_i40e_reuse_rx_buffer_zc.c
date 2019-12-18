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
struct i40e_rx_buffer {int /*<<< orphan*/ * addr; int /*<<< orphan*/  handle; int /*<<< orphan*/  dma; } ;
struct i40e_ring {size_t next_to_alloc; scalar_t__ count; struct i40e_rx_buffer* rx_bi; } ;

/* Variables and functions */

__attribute__((used)) static void i40e_reuse_rx_buffer_zc(struct i40e_ring *rx_ring,
				    struct i40e_rx_buffer *old_bi)
{
	struct i40e_rx_buffer *new_bi = &rx_ring->rx_bi[rx_ring->next_to_alloc];
	u16 nta = rx_ring->next_to_alloc;

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	new_bi->dma = old_bi->dma;
	new_bi->addr = old_bi->addr;
	new_bi->handle = old_bi->handle;

	old_bi->addr = NULL;
}