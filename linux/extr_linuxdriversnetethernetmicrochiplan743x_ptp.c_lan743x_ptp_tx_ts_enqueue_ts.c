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
typedef  void* u32 ;
struct lan743x_ptp {size_t tx_ts_queue_size; int /*<<< orphan*/  tx_ts_lock; void** tx_ts_header_queue; void** tx_ts_nseconds_queue; void** tx_ts_seconds_queue; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; struct lan743x_ptp ptp; } ;

/* Variables and functions */
 size_t LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_ptp_tx_ts_enqueue_ts(struct lan743x_adapter *adapter,
					 u32 seconds, u32 nano_seconds,
					 u32 header)
{
	struct lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	if (ptp->tx_ts_queue_size < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) {
		ptp->tx_ts_seconds_queue[ptp->tx_ts_queue_size] = seconds;
		ptp->tx_ts_nseconds_queue[ptp->tx_ts_queue_size] = nano_seconds;
		ptp->tx_ts_header_queue[ptp->tx_ts_queue_size] = header;
		ptp->tx_ts_queue_size++;
	} else {
		netif_err(adapter, drv, adapter->netdev,
			  "tx ts queue overflow\n");
	}
	spin_unlock_bh(&ptp->tx_ts_lock);
}