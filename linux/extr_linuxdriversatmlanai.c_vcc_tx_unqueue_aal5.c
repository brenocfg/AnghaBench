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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct lanai_vcc {int /*<<< orphan*/  vci; TYPE_1__ tx; } ;
struct lanai_dev {int /*<<< orphan*/  backlog_vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aal5_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_send_one_aal5 (struct lanai_dev*,struct lanai_vcc*,struct sk_buff*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  vcc_is_backlogged (struct lanai_vcc*) ; 
 int vcc_tx_space (struct lanai_vcc*,int) ; 

__attribute__((used)) static void vcc_tx_unqueue_aal5(struct lanai_dev *lanai,
	struct lanai_vcc *lvcc, int endptr)
{
	int n;
	struct sk_buff *skb;
	int space = vcc_tx_space(lvcc, endptr);
	APRINTK(vcc_is_backlogged(lvcc),
	    "vcc_tx_unqueue() called with empty backlog (vci=%d)\n",
	    lvcc->vci);
	while (space >= 64) {
		skb = skb_dequeue(&lvcc->tx.backlog);
		if (skb == NULL)
			goto no_backlog;
		n = aal5_size(skb->len);
		if (n + 16 > space) {
			/* No room for this packet - put it back on queue */
			skb_queue_head(&lvcc->tx.backlog, skb);
			return;
		}
		lanai_send_one_aal5(lanai, lvcc, skb, n);
		space -= n + 16;
	}
	if (!vcc_is_backlogged(lvcc)) {
	    no_backlog:
		__clear_bit(lvcc->vci, lanai->backlog_vccs);
	}
}