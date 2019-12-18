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
struct ixgbevf_ring {TYPE_1__ tx_stats; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_HANG_CHECK_ARMED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_check_for_tx_hang (struct ixgbevf_ring*) ; 
 scalar_t__ ixgbevf_get_tx_completed (struct ixgbevf_ring*) ; 
 scalar_t__ ixgbevf_get_tx_pending (struct ixgbevf_ring*) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ixgbevf_check_tx_hang(struct ixgbevf_ring *tx_ring)
{
	u32 tx_done = ixgbevf_get_tx_completed(tx_ring);
	u32 tx_done_old = tx_ring->tx_stats.tx_done_old;
	u32 tx_pending = ixgbevf_get_tx_pending(tx_ring);

	clear_check_for_tx_hang(tx_ring);

	/* Check for a hung queue, but be thorough. This verifies
	 * that a transmit has been completed since the previous
	 * check AND there is at least one packet pending. The
	 * ARMED bit is set to indicate a potential hang.
	 */
	if ((tx_done_old == tx_done) && tx_pending) {
		/* make sure it is true for two checks in a row */
		return test_and_set_bit(__IXGBEVF_HANG_CHECK_ARMED,
					&tx_ring->state);
	}
	/* reset the countdown */
	clear_bit(__IXGBEVF_HANG_CHECK_ARMED, &tx_ring->state);

	/* update completed stats and continue */
	tx_ring->tx_stats.tx_done_old = tx_done;

	return false;
}