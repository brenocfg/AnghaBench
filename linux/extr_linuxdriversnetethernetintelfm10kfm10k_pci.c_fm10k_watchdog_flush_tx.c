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
struct fm10k_ring {scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct fm10k_intfc {int num_tx_queues; int /*<<< orphan*/  flags; struct fm10k_ring** tx_ring; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_FLAG_RESET_REQUESTED ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_watchdog_flush_tx(struct fm10k_intfc *interface)
{
	int some_tx_pending = 0;
	int i;

	/* nothing to do if carrier is up */
	if (netif_carrier_ok(interface->netdev))
		return;

	for (i = 0; i < interface->num_tx_queues; i++) {
		struct fm10k_ring *tx_ring = interface->tx_ring[i];

		if (tx_ring->next_to_use != tx_ring->next_to_clean) {
			some_tx_pending = 1;
			break;
		}
	}

	/* We've lost link, so the controller stops DMA, but we've got
	 * queued Tx work that's never going to get done, so reset
	 * controller to flush Tx.
	 */
	if (some_tx_pending)
		set_bit(FM10K_FLAG_RESET_REQUESTED, interface->flags);
}