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
struct i40e_tx_buffer {int dummy; } ;
struct i40e_ring {size_t count; unsigned long size; int /*<<< orphan*/  netdev; scalar_t__ next_to_clean; scalar_t__ next_to_use; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * tx_bi; scalar_t__ xsk_umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_unmap_and_free_tx_resource (struct i40e_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_xsk_clean_tx_ring (struct i40e_ring*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_is_xdp (struct i40e_ring*) ; 
 int /*<<< orphan*/  txring_txq (struct i40e_ring*) ; 

void i40e_clean_tx_ring(struct i40e_ring *tx_ring)
{
	unsigned long bi_size;
	u16 i;

	if (ring_is_xdp(tx_ring) && tx_ring->xsk_umem) {
		i40e_xsk_clean_tx_ring(tx_ring);
	} else {
		/* ring already cleared, nothing to do */
		if (!tx_ring->tx_bi)
			return;

		/* Free all the Tx ring sk_buffs */
		for (i = 0; i < tx_ring->count; i++)
			i40e_unmap_and_free_tx_resource(tx_ring,
							&tx_ring->tx_bi[i]);
	}

	bi_size = sizeof(struct i40e_tx_buffer) * tx_ring->count;
	memset(tx_ring->tx_bi, 0, bi_size);

	/* Zero out the descriptor ring */
	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	if (!tx_ring->netdev)
		return;

	/* cleanup Tx queue statistics */
	netdev_tx_reset_queue(txring_txq(tx_ring));
}