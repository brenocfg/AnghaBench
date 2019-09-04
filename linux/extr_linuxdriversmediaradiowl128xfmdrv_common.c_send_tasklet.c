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
struct fmdev {scalar_t__ last_tx_jiffies; int /*<<< orphan*/  tx_cnt; int /*<<< orphan*/ * resp_comp; int /*<<< orphan*/  pre_op; int /*<<< orphan*/  tx_q; } ;
struct TYPE_2__ {int /*<<< orphan*/ * completion; int /*<<< orphan*/  fm_op; } ;

/* Variables and functions */
 scalar_t__ FM_DRV_TX_TIMEOUT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* fm_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  fmerr (char*,...) ; 
 int g_st_write (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_tasklet(unsigned long arg)
{
	struct fmdev *fmdev;
	struct sk_buff *skb;
	int len;

	fmdev = (struct fmdev *)arg;

	if (!atomic_read(&fmdev->tx_cnt))
		return;

	/* Check, is there any timeout happened to last transmitted packet */
	if ((jiffies - fmdev->last_tx_jiffies) > FM_DRV_TX_TIMEOUT) {
		fmerr("TX timeout occurred\n");
		atomic_set(&fmdev->tx_cnt, 1);
	}

	/* Send queued FM TX packets */
	skb = skb_dequeue(&fmdev->tx_q);
	if (!skb)
		return;

	atomic_dec(&fmdev->tx_cnt);
	fmdev->pre_op = fm_cb(skb)->fm_op;

	if (fmdev->resp_comp != NULL)
		fmerr("Response completion handler is not NULL\n");

	fmdev->resp_comp = fm_cb(skb)->completion;

	/* Write FM packet to ST driver */
	len = g_st_write(skb);
	if (len < 0) {
		kfree_skb(skb);
		fmdev->resp_comp = NULL;
		fmerr("TX tasklet failed to send skb(%p)\n", skb);
		atomic_set(&fmdev->tx_cnt, 1);
	} else {
		fmdev->last_tx_jiffies = jiffies;
	}
}