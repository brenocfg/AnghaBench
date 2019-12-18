#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ tx_done_old; } ;
struct fm10k_ring {int /*<<< orphan*/  state; TYPE_1__ tx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  __FM10K_HANG_CHECK_ARMED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_check_for_tx_hang (struct fm10k_ring*) ; 
 scalar_t__ fm10k_get_tx_completed (struct fm10k_ring*) ; 
 scalar_t__ fm10k_get_tx_pending (struct fm10k_ring*,int) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool fm10k_check_tx_hang(struct fm10k_ring *tx_ring)
{
	u32 tx_done = fm10k_get_tx_completed(tx_ring);
	u32 tx_done_old = tx_ring->tx_stats.tx_done_old;
	u32 tx_pending = fm10k_get_tx_pending(tx_ring, true);

	clear_check_for_tx_hang(tx_ring);

	/* Check for a hung queue, but be thorough. This verifies
	 * that a transmit has been completed since the previous
	 * check AND there is at least one packet pending. By
	 * requiring this to fail twice we avoid races with
	 * clearing the ARMED bit and conditions where we
	 * run the check_tx_hang logic with a transmit completion
	 * pending but without time to complete it yet.
	 */
	if (!tx_pending || (tx_done_old != tx_done)) {
		/* update completed stats and continue */
		tx_ring->tx_stats.tx_done_old = tx_done;
		/* reset the countdown */
		clear_bit(__FM10K_HANG_CHECK_ARMED, tx_ring->state);

		return false;
	}

	/* make sure it is true for two checks in a row */
	return test_and_set_bit(__FM10K_HANG_CHECK_ARMED, tx_ring->state);
}