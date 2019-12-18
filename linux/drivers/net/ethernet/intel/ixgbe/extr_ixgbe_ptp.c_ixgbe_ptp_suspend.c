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
struct ixgbe_adapter {int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  (* ptp_setup_sdp ) (struct ixgbe_adapter*) ;int /*<<< orphan*/  flags2; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FLAG2_PTP_PPS_ENABLED ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_ptp_clear_tx_timestamp (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbe_ptp_suspend(struct ixgbe_adapter *adapter)
{
	/* Leave the IXGBE_PTP_RUNNING state. */
	if (!test_and_clear_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		return;

	adapter->flags2 &= ~IXGBE_FLAG2_PTP_PPS_ENABLED;
	if (adapter->ptp_setup_sdp)
		adapter->ptp_setup_sdp(adapter);

	/* ensure that we cancel any pending PTP Tx work item in progress */
	cancel_work_sync(&adapter->ptp_tx_work);
	ixgbe_ptp_clear_tx_timestamp(adapter);
}