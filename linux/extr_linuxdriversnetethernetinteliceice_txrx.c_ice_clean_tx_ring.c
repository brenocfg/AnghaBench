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
struct ice_tx_buf {int dummy; } ;
struct ice_ring {size_t count; unsigned long size; int /*<<< orphan*/  netdev; scalar_t__ next_to_clean; scalar_t__ next_to_use; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_unmap_and_free_tx_buf (struct ice_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct ice_ring*) ; 

void ice_clean_tx_ring(struct ice_ring *tx_ring)
{
	unsigned long size;
	u16 i;

	/* ring already cleared, nothing to do */
	if (!tx_ring->tx_buf)
		return;

	/* Free all the Tx ring sk_bufss */
	for (i = 0; i < tx_ring->count; i++)
		ice_unmap_and_free_tx_buf(tx_ring, &tx_ring->tx_buf[i]);

	size = sizeof(struct ice_tx_buf) * tx_ring->count;
	memset(tx_ring->tx_buf, 0, size);

	/* Zero out the descriptor ring */
	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	if (!tx_ring->netdev)
		return;

	/* cleanup Tx queue statistics */
	netdev_tx_reset_queue(txring_txq(tx_ring));
}