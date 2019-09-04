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
struct sk_buff {unsigned int len; } ;
struct cardstate {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_tasklet; scalar_t__ connected; int /*<<< orphan*/  dev; } ;
struct bc_state {scalar_t__ proto2; int /*<<< orphan*/  squeue; struct cardstate* cs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* HDLC_Encode (struct sk_buff*) ; 
 scalar_t__ L2_HDLC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* iraw_encode (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

int gigaset_m10x_send_skb(struct bc_state *bcs, struct sk_buff *skb)
{
	struct cardstate *cs = bcs->cs;
	unsigned len = skb->len;
	unsigned long flags;

	if (bcs->proto2 == L2_HDLC)
		skb = HDLC_Encode(skb);
	else
		skb = iraw_encode(skb);
	if (!skb) {
		dev_err(cs->dev,
			"unable to allocate memory for encoding!\n");
		return -ENOMEM;
	}

	skb_queue_tail(&bcs->squeue, skb);
	spin_lock_irqsave(&cs->lock, flags);
	if (cs->connected)
		tasklet_schedule(&cs->write_tasklet);
	spin_unlock_irqrestore(&cs->lock, flags);

	return len;	/* ok so far */
}