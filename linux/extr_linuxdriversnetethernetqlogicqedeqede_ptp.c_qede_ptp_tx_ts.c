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
struct sk_buff {int dummy; } ;
struct qede_ptp {int tx_skb; int /*<<< orphan*/  work; } ;
struct qede_dev {int flags; struct qede_ptp* ptp; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  QEDE_FLAGS_PTP_TX_IN_PRORGESS ; 
 int QEDE_TX_TIMESTAMPING_EN ; 
 int /*<<< orphan*/  SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int skb_get (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

void qede_ptp_tx_ts(struct qede_dev *edev, struct sk_buff *skb)
{
	struct qede_ptp *ptp;

	ptp = edev->ptp;
	if (!ptp)
		return;

	if (test_and_set_bit_lock(QEDE_FLAGS_PTP_TX_IN_PRORGESS, &edev->flags))
		return;

	if (unlikely(!(edev->flags & QEDE_TX_TIMESTAMPING_EN))) {
		DP_NOTICE(edev,
			  "Tx timestamping was not enabled, this packet will not be timestamped\n");
	} else if (unlikely(ptp->tx_skb)) {
		DP_NOTICE(edev,
			  "The device supports only a single outstanding packet to timestamp, this packet will not be timestamped\n");
	} else {
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		/* schedule check for Tx timestamp */
		ptp->tx_skb = skb_get(skb);
		schedule_work(&ptp->work);
	}
}