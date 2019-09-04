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
struct ixgbe_adapter {int /*<<< orphan*/  tx_hwtstamp_timeouts; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  state; int /*<<< orphan*/  ptp_tx_skb; scalar_t__ ptp_tx_start; } ;

/* Variables and functions */
 scalar_t__ IXGBE_PTP_TX_TIMEOUT ; 
 int /*<<< orphan*/  __IXGBE_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixgbe_ptp_clear_tx_timestamp (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int time_is_before_jiffies (scalar_t__) ; 

void ixgbe_ptp_tx_hang(struct ixgbe_adapter *adapter)
{
	bool timeout = time_is_before_jiffies(adapter->ptp_tx_start +
					      IXGBE_PTP_TX_TIMEOUT);

	if (!adapter->ptp_tx_skb)
		return;

	if (!test_bit(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state))
		return;

	/* If we haven't received a timestamp within the timeout, it is
	 * reasonable to assume that it will never occur, so we can unlock the
	 * timestamp bit when this occurs.
	 */
	if (timeout) {
		cancel_work_sync(&adapter->ptp_tx_work);
		ixgbe_ptp_clear_tx_timestamp(adapter);
		adapter->tx_hwtstamp_timeouts++;
		e_warn(drv, "clearing Tx timestamp hang\n");
	}
}