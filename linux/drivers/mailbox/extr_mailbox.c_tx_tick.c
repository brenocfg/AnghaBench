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
struct mbox_chan {int /*<<< orphan*/  tx_complete; TYPE_1__* cl; int /*<<< orphan*/  lock; int /*<<< orphan*/ * active_req; } ;
struct TYPE_2__ {scalar_t__ tx_block; int /*<<< orphan*/  (* tx_done ) (TYPE_1__*,void*,int) ;} ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_submit (struct mbox_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,int) ; 

__attribute__((used)) static void tx_tick(struct mbox_chan *chan, int r)
{
	unsigned long flags;
	void *mssg;

	spin_lock_irqsave(&chan->lock, flags);
	mssg = chan->active_req;
	chan->active_req = NULL;
	spin_unlock_irqrestore(&chan->lock, flags);

	/* Submit next message */
	msg_submit(chan);

	if (!mssg)
		return;

	/* Notify the client */
	if (chan->cl->tx_done)
		chan->cl->tx_done(chan->cl, mssg, r);

	if (r != -ETIME && chan->cl->tx_block)
		complete(&chan->tx_complete);
}