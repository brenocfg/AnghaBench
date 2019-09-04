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
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int flags2; int flags; int num_tx_queues; int num_xdp_queues; TYPE_2__** xdp_ring; TYPE_1__** tx_ring; int /*<<< orphan*/  fdir_overflow; int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EIMS ; 
 int /*<<< orphan*/  IXGBE_EIMS_FLOW_DIR ; 
 int IXGBE_FLAG2_FDIR_REQUIRES_REINIT ; 
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  __IXGBE_TX_FDIR_INIT_DONE ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ixgbe_reinit_fdir_tables_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_fdir_reinit_subtask(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	if (!(adapter->flags2 & IXGBE_FLAG2_FDIR_REQUIRES_REINIT))
		return;

	adapter->flags2 &= ~IXGBE_FLAG2_FDIR_REQUIRES_REINIT;

	/* if interface is down do nothing */
	if (test_bit(__IXGBE_DOWN, &adapter->state))
		return;

	/* do nothing if we are not using signature filters */
	if (!(adapter->flags & IXGBE_FLAG_FDIR_HASH_CAPABLE))
		return;

	adapter->fdir_overflow++;

	if (ixgbe_reinit_fdir_tables_82599(hw) == 0) {
		for (i = 0; i < adapter->num_tx_queues; i++)
			set_bit(__IXGBE_TX_FDIR_INIT_DONE,
				&(adapter->tx_ring[i]->state));
		for (i = 0; i < adapter->num_xdp_queues; i++)
			set_bit(__IXGBE_TX_FDIR_INIT_DONE,
				&adapter->xdp_ring[i]->state);
		/* re-enable flow director interrupts */
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMS_FLOW_DIR);
	} else {
		e_err(probe, "failed to finish FDIR re-initialization, "
		      "ignored adding FDIR ATR filters\n");
	}
}