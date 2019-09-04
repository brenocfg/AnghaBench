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
struct igb_adapter {int ptp_flags; int /*<<< orphan*/  state; int /*<<< orphan*/ * ptp_tx_skb; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  ptp_overflow_work; } ;

/* Variables and functions */
 int IGB_PTP_ENABLED ; 
 int IGB_PTP_OVERFLOW_CHECK ; 
 int /*<<< orphan*/  __IGB_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 

void igb_ptp_suspend(struct igb_adapter *adapter)
{
	if (!(adapter->ptp_flags & IGB_PTP_ENABLED))
		return;

	if (adapter->ptp_flags & IGB_PTP_OVERFLOW_CHECK)
		cancel_delayed_work_sync(&adapter->ptp_overflow_work);

	cancel_work_sync(&adapter->ptp_tx_work);
	if (adapter->ptp_tx_skb) {
		dev_kfree_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = NULL;
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
	}
}