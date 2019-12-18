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
struct i40e_rx_buffer {int /*<<< orphan*/ * addr; int /*<<< orphan*/  handle; } ;
struct i40e_ring {size_t count; int /*<<< orphan*/  xsk_umem; struct i40e_rx_buffer* rx_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsk_umem_fq_reuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_xsk_clean_rx_ring(struct i40e_ring *rx_ring)
{
	u16 i;

	for (i = 0; i < rx_ring->count; i++) {
		struct i40e_rx_buffer *rx_bi = &rx_ring->rx_bi[i];

		if (!rx_bi->addr)
			continue;

		xsk_umem_fq_reuse(rx_ring->xsk_umem, rx_bi->handle);
		rx_bi->addr = NULL;
	}
}