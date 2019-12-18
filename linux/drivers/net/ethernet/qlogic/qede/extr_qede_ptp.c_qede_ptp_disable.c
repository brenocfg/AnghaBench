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
struct qede_ptp {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  work; int /*<<< orphan*/ * clock; } ;
struct qede_dev {struct qede_ptp* ptp; int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qede_ptp*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void qede_ptp_disable(struct qede_dev *edev)
{
	struct qede_ptp *ptp;

	ptp = edev->ptp;
	if (!ptp)
		return;

	if (ptp->clock) {
		ptp_clock_unregister(ptp->clock);
		ptp->clock = NULL;
	}

	/* Cancel PTP work queue. Should be done after the Tx queues are
	 * drained to prevent additional scheduling.
	 */
	cancel_work_sync(&ptp->work);
	if (ptp->tx_skb) {
		dev_kfree_skb_any(ptp->tx_skb);
		ptp->tx_skb = NULL;
	}

	/* Disable PTP in HW */
	spin_lock_bh(&ptp->lock);
	ptp->ops->disable(edev->cdev);
	spin_unlock_bh(&ptp->lock);

	kfree(ptp);
	edev->ptp = NULL;
}