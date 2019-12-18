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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct qede_ptp {int /*<<< orphan*/  lock; int /*<<< orphan*/  tc; TYPE_1__* ops; } ;
struct qede_dev {int /*<<< orphan*/  cdev; struct qede_ptp* ptp; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwtstamp; } ;
struct TYPE_3__ {int (* read_rx_ts ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qede_ptp_rx_ts(struct qede_dev *edev, struct sk_buff *skb)
{
	struct qede_ptp *ptp;
	u64 timestamp, ns;
	int rc;

	ptp = edev->ptp;
	if (!ptp)
		return;

	spin_lock_bh(&ptp->lock);
	rc = ptp->ops->read_rx_ts(edev->cdev, &timestamp);
	if (rc) {
		spin_unlock_bh(&ptp->lock);
		DP_INFO(edev, "Invalid Rx timestamp\n");
		return;
	}

	ns = timecounter_cyc2time(&ptp->tc, timestamp);
	spin_unlock_bh(&ptp->lock);
	skb_hwtstamps(skb)->hwtstamp = ns_to_ktime(ns);
	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Rx timestamp, timestamp cycles = %llu, ns = %llu\n",
		   timestamp, ns);
}