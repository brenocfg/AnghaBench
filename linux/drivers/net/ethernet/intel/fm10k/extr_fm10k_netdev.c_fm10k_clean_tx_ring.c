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
struct fm10k_tx_buffer {int dummy; } ;
struct fm10k_ring {size_t count; unsigned long size; struct fm10k_tx_buffer* desc; struct fm10k_tx_buffer* tx_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_unmap_and_free_tx_resource (struct fm10k_ring*,struct fm10k_tx_buffer*) ; 
 int /*<<< orphan*/  memset (struct fm10k_tx_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct fm10k_ring*) ; 

__attribute__((used)) static void fm10k_clean_tx_ring(struct fm10k_ring *tx_ring)
{
	unsigned long size;
	u16 i;

	/* ring already cleared, nothing to do */
	if (!tx_ring->tx_buffer)
		return;

	/* Free all the Tx ring sk_buffs */
	for (i = 0; i < tx_ring->count; i++) {
		struct fm10k_tx_buffer *tx_buffer = &tx_ring->tx_buffer[i];

		fm10k_unmap_and_free_tx_resource(tx_ring, tx_buffer);
	}

	/* reset BQL values */
	netdev_tx_reset_queue(txring_txq(tx_ring));

	size = sizeof(struct fm10k_tx_buffer) * tx_ring->count;
	memset(tx_ring->tx_buffer, 0, size);

	/* Zero out the descriptor ring */
	memset(tx_ring->desc, 0, tx_ring->size);
}