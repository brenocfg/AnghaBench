#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ppp_channel {struct channel* ppp; } ;
struct TYPE_11__ {scalar_t__ qlen; } ;
struct TYPE_10__ {int /*<<< orphan*/  rwait; TYPE_4__ rq; } ;
struct channel {int /*<<< orphan*/  upl; TYPE_6__* ppp; TYPE_3__ file; } ;
struct TYPE_12__ {TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_9__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int PPP_CCPFRAG ; 
 scalar_t__ PPP_MAX_RQLEN ; 
 int PPP_PROTO (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_decompress_proto (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_do_recv (TYPE_6__*,struct sk_buff*,struct channel*) ; 
 int /*<<< orphan*/  ppp_receive_error (TYPE_6__*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (TYPE_4__*) ; 
 int /*<<< orphan*/  skb_queue_tail (TYPE_4__*,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
ppp_input(struct ppp_channel *chan, struct sk_buff *skb)
{
	struct channel *pch = chan->ppp;
	int proto;

	if (!pch) {
		kfree_skb(skb);
		return;
	}

	read_lock_bh(&pch->upl);
	if (!ppp_decompress_proto(skb)) {
		kfree_skb(skb);
		if (pch->ppp) {
			++pch->ppp->dev->stats.rx_length_errors;
			ppp_receive_error(pch->ppp);
		}
		goto done;
	}

	proto = PPP_PROTO(skb);
	if (!pch->ppp || proto >= 0xc000 || proto == PPP_CCPFRAG) {
		/* put it on the channel queue */
		skb_queue_tail(&pch->file.rq, skb);
		/* drop old frames if queue too long */
		while (pch->file.rq.qlen > PPP_MAX_RQLEN &&
		       (skb = skb_dequeue(&pch->file.rq)))
			kfree_skb(skb);
		wake_up_interruptible(&pch->file.rwait);
	} else {
		ppp_do_recv(pch->ppp, skb, pch);
	}

done:
	read_unlock_bh(&pch->upl);
}