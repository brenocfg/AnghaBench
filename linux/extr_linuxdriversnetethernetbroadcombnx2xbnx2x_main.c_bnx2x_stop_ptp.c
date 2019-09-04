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
struct bnx2x {int /*<<< orphan*/ * ptp_tx_skb; int /*<<< orphan*/  ptp_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_PTP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bnx2x_disable_ptp (struct bnx2x*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_stop_ptp(struct bnx2x *bp)
{
	/* Cancel PTP work queue. Should be done after the Tx queues are
	 * drained to prevent additional scheduling.
	 */
	cancel_work_sync(&bp->ptp_task);

	if (bp->ptp_tx_skb) {
		dev_kfree_skb_any(bp->ptp_tx_skb);
		bp->ptp_tx_skb = NULL;
	}

	/* Disable PTP in HW */
	bnx2x_disable_ptp(bp);

	DP(BNX2X_MSG_PTP, "PTP stop ended successfully\n");
}