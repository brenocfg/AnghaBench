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
struct lan743x_adapter {int /*<<< orphan*/  netdev; struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void lan743x_ptp_unrequest_tx_timestamp(struct lan743x_adapter *adapter)
{
	struct lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	if (ptp->pending_tx_timestamps > 0)
		ptp->pending_tx_timestamps--;
	else
		netif_err(adapter, drv, adapter->netdev,
			  "unrequest failed, pending_tx_timestamps==0\n");
	spin_unlock_bh(&ptp->tx_ts_lock);
}