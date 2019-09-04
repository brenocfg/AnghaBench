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
struct e1000_hw {int dummy; } ;
struct igb_adapter {TYPE_1__* pdev; int /*<<< orphan*/  tx_hwtstamp_timeouts; int /*<<< orphan*/  state; int /*<<< orphan*/ * ptp_tx_skb; int /*<<< orphan*/  ptp_tx_work; scalar_t__ ptp_tx_start; struct e1000_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TXSTMPH ; 
 scalar_t__ IGB_PTP_TX_TIMEOUT ; 
 int /*<<< orphan*/  __IGB_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int time_is_before_jiffies (scalar_t__) ; 

void igb_ptp_tx_hang(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	bool timeout = time_is_before_jiffies(adapter->ptp_tx_start +
					      IGB_PTP_TX_TIMEOUT);

	if (!adapter->ptp_tx_skb)
		return;

	if (!test_bit(__IGB_PTP_TX_IN_PROGRESS, &adapter->state))
		return;

	/* If we haven't received a timestamp within the timeout, it is
	 * reasonable to assume that it will never occur, so we can unlock the
	 * timestamp bit when this occurs.
	 */
	if (timeout) {
		cancel_work_sync(&adapter->ptp_tx_work);
		dev_kfree_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = NULL;
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
		adapter->tx_hwtstamp_timeouts++;
		/* Clear the tx valid bit in TSYNCTXCTL register to enable
		 * interrupt
		 */
		rd32(E1000_TXSTMPH);
		dev_warn(&adapter->pdev->dev, "clearing Tx timestamp hang\n");
	}
}