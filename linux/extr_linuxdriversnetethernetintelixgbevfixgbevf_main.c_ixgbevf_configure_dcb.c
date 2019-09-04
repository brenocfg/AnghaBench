#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ timeout; } ;
struct ixgbe_hw {TYPE_2__ mbx; } ;
struct ixgbevf_adapter {unsigned int num_rx_queues; unsigned int num_tx_queues; int /*<<< orphan*/  state; TYPE_1__** tx_ring; int /*<<< orphan*/  mbx_lock; struct ixgbe_hw hw; } ;
struct TYPE_3__ {unsigned int reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBEVF_QUEUE_RESET_REQUESTED ; 
 int ixgbevf_get_queues (struct ixgbe_hw*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbevf_configure_dcb(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	unsigned int def_q = 0;
	unsigned int num_tcs = 0;
	unsigned int num_rx_queues = adapter->num_rx_queues;
	unsigned int num_tx_queues = adapter->num_tx_queues;
	int err;

	spin_lock_bh(&adapter->mbx_lock);

	/* fetch queue configuration from the PF */
	err = ixgbevf_get_queues(hw, &num_tcs, &def_q);

	spin_unlock_bh(&adapter->mbx_lock);

	if (err)
		return err;

	if (num_tcs > 1) {
		/* we need only one Tx queue */
		num_tx_queues = 1;

		/* update default Tx ring register index */
		adapter->tx_ring[0]->reg_idx = def_q;

		/* we need as many queues as traffic classes */
		num_rx_queues = num_tcs;
	}

	/* if we have a bad config abort request queue reset */
	if ((adapter->num_rx_queues != num_rx_queues) ||
	    (adapter->num_tx_queues != num_tx_queues)) {
		/* force mailbox timeout to prevent further messages */
		hw->mbx.timeout = 0;

		/* wait for watchdog to come around and bail us out */
		set_bit(__IXGBEVF_QUEUE_RESET_REQUESTED, &adapter->state);
	}

	return 0;
}