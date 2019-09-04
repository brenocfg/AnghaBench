#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbox_chan {scalar_t__ txdone_method; int /*<<< orphan*/  lock; TYPE_3__* mbox; int /*<<< orphan*/ * active_req; int /*<<< orphan*/ * cl; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* shutdown ) (struct mbox_chan*) ;} ;
struct TYPE_7__ {TYPE_2__* dev; TYPE_4__* ops; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ TXDONE_BY_ACK ; 
 scalar_t__ TXDONE_BY_POLL ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mbox_chan*) ; 

void mbox_free_channel(struct mbox_chan *chan)
{
	unsigned long flags;

	if (!chan || !chan->cl)
		return;

	if (chan->mbox->ops->shutdown)
		chan->mbox->ops->shutdown(chan);

	/* The queued TX requests are simply aborted, no callbacks are made */
	spin_lock_irqsave(&chan->lock, flags);
	chan->cl = NULL;
	chan->active_req = NULL;
	if (chan->txdone_method == TXDONE_BY_ACK)
		chan->txdone_method = TXDONE_BY_POLL;

	module_put(chan->mbox->dev->driver->owner);
	spin_unlock_irqrestore(&chan->lock, flags);
}