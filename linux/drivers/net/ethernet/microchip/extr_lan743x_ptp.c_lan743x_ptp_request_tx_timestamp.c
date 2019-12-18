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
struct lan743x_ptp {scalar_t__ pending_tx_timestamps; int /*<<< orphan*/  tx_ts_lock; } ;
struct lan743x_adapter {struct lan743x_ptp ptp; } ;

/* Variables and functions */
 scalar_t__ LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool lan743x_ptp_request_tx_timestamp(struct lan743x_adapter *adapter)
{
	struct lan743x_ptp *ptp = &adapter->ptp;
	bool result = false;

	spin_lock_bh(&ptp->tx_ts_lock);
	if (ptp->pending_tx_timestamps < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) {
		/* request granted */
		ptp->pending_tx_timestamps++;
		result = true;
	}
	spin_unlock_bh(&ptp->tx_ts_lock);
	return result;
}