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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct ixgbe_tx_buffer {int /*<<< orphan*/ * xdpf; } ;
struct ixgbe_ring {size_t next_to_clean; size_t next_to_use; size_t count; struct ixgbe_tx_buffer* tx_buffer_info; struct xdp_umem* xsk_umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_clean_xdp_tx_buffer (struct ixgbe_ring*,struct ixgbe_tx_buffer*) ; 
 int /*<<< orphan*/  xsk_umem_complete_tx (struct xdp_umem*,scalar_t__) ; 

void ixgbe_xsk_clean_tx_ring(struct ixgbe_ring *tx_ring)
{
	u16 ntc = tx_ring->next_to_clean, ntu = tx_ring->next_to_use;
	struct xdp_umem *umem = tx_ring->xsk_umem;
	struct ixgbe_tx_buffer *tx_bi;
	u32 xsk_frames = 0;

	while (ntc != ntu) {
		tx_bi = &tx_ring->tx_buffer_info[ntc];

		if (tx_bi->xdpf)
			ixgbe_clean_xdp_tx_buffer(tx_ring, tx_bi);
		else
			xsk_frames++;

		tx_bi->xdpf = NULL;

		ntc++;
		if (ntc == tx_ring->count)
			ntc = 0;
	}

	if (xsk_frames)
		xsk_umem_complete_tx(umem, xsk_frames);
}