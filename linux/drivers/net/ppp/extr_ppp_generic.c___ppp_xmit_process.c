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
struct TYPE_2__ {int /*<<< orphan*/  xq; } ;
struct ppp {int /*<<< orphan*/  dev; TYPE_1__ file; int /*<<< orphan*/  xmit_pending; int /*<<< orphan*/  closing; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_push (struct ppp*) ; 
 int /*<<< orphan*/  ppp_send_frame (struct ppp*,struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_xmit_lock (struct ppp*) ; 
 int /*<<< orphan*/  ppp_xmit_unlock (struct ppp*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void __ppp_xmit_process(struct ppp *ppp, struct sk_buff *skb)
{
	ppp_xmit_lock(ppp);
	if (!ppp->closing) {
		ppp_push(ppp);

		if (skb)
			skb_queue_tail(&ppp->file.xq, skb);
		while (!ppp->xmit_pending &&
		       (skb = skb_dequeue(&ppp->file.xq)))
			ppp_send_frame(ppp, skb);
		/* If there's no work left to do, tell the core net
		   code that we can accept some more. */
		if (!ppp->xmit_pending && !skb_peek(&ppp->file.xq))
			netif_wake_queue(ppp->dev);
		else
			netif_stop_queue(ppp->dev);
	} else {
		kfree_skb(skb);
	}
	ppp_xmit_unlock(ppp);
}