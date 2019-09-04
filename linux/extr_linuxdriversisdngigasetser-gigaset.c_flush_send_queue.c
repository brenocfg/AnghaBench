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
struct cmdbuf_t {scalar_t__ wake_tasklet; struct cmdbuf_t* next; } ;
struct cardstate {TYPE_1__* bcs; int /*<<< orphan*/  cmdlock; scalar_t__ curlen; scalar_t__ cmdbytes; int /*<<< orphan*/ * lastcmdbuf; struct cmdbuf_t* cmdbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  squeue; struct sk_buff* tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct cmdbuf_t*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (scalar_t__) ; 

__attribute__((used)) static void flush_send_queue(struct cardstate *cs)
{
	struct sk_buff *skb;
	struct cmdbuf_t *cb;
	unsigned long flags;

	/* command queue */
	spin_lock_irqsave(&cs->cmdlock, flags);
	while ((cb = cs->cmdbuf) != NULL) {
		cs->cmdbuf = cb->next;
		if (cb->wake_tasklet)
			tasklet_schedule(cb->wake_tasklet);
		kfree(cb);
	}
	cs->cmdbuf = cs->lastcmdbuf = NULL;
	cs->cmdbytes = cs->curlen = 0;
	spin_unlock_irqrestore(&cs->cmdlock, flags);

	/* data queue */
	if (cs->bcs->tx_skb)
		dev_kfree_skb_any(cs->bcs->tx_skb);
	while ((skb = skb_dequeue(&cs->bcs->squeue)) != NULL)
		dev_kfree_skb_any(skb);
}