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
struct mbox_chan {int msg_count; int msg_free; int /*<<< orphan*/  lock; void** msg_data; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int MBOX_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int add_to_rbuf(struct mbox_chan *chan, void *mssg)
{
	int idx;
	unsigned long flags;

	spin_lock_irqsave(&chan->lock, flags);

	/* See if there is any space left */
	if (chan->msg_count == MBOX_TX_QUEUE_LEN) {
		spin_unlock_irqrestore(&chan->lock, flags);
		return -ENOBUFS;
	}

	idx = chan->msg_free;
	chan->msg_data[idx] = mssg;
	chan->msg_count++;

	if (idx == MBOX_TX_QUEUE_LEN - 1)
		chan->msg_free = 0;
	else
		chan->msg_free++;

	spin_unlock_irqrestore(&chan->lock, flags);

	return idx;
}