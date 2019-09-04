#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbox_chan {unsigned int msg_count; unsigned int msg_free; int txdone_method; TYPE_2__* mbox; int /*<<< orphan*/  lock; void* active_req; TYPE_3__* cl; void** msg_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tx_prepare ) (TYPE_3__*,void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  poll_hrt; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* send_data ) (struct mbox_chan*,void*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 unsigned int MBOX_TX_QUEUE_LEN ; 
 int TXDONE_BY_POLL ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*) ; 
 int stub2 (struct mbox_chan*,void*) ; 

__attribute__((used)) static void msg_submit(struct mbox_chan *chan)
{
	unsigned count, idx;
	unsigned long flags;
	void *data;
	int err = -EBUSY;

	spin_lock_irqsave(&chan->lock, flags);

	if (!chan->msg_count || chan->active_req)
		goto exit;

	count = chan->msg_count;
	idx = chan->msg_free;
	if (idx >= count)
		idx -= count;
	else
		idx += MBOX_TX_QUEUE_LEN - count;

	data = chan->msg_data[idx];

	if (chan->cl->tx_prepare)
		chan->cl->tx_prepare(chan->cl, data);
	/* Try to submit a message to the MBOX controller */
	err = chan->mbox->ops->send_data(chan, data);
	if (!err) {
		chan->active_req = data;
		chan->msg_count--;
	}
exit:
	spin_unlock_irqrestore(&chan->lock, flags);

	if (!err && (chan->txdone_method & TXDONE_BY_POLL))
		/* kick start the timer immediately to avoid delays */
		hrtimer_start(&chan->mbox->poll_hrt, 0, HRTIMER_MODE_REL);
}