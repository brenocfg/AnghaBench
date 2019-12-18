#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {int /*<<< orphan*/  stream; TYPE_2__** bufs; TYPE_1__* ops; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  wait; scalar_t__ reading; scalar_t__ streaming; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  done; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* buf_release ) (struct videobuf_queue*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ VIDEOBUF_ERROR ; 
 scalar_t__ VIDEOBUF_QUEUED ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct videobuf_queue*,TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

void videobuf_queue_cancel(struct videobuf_queue *q)
{
	unsigned long flags = 0;
	int i;

	q->streaming = 0;
	q->reading  = 0;
	wake_up_interruptible_sync(&q->wait);

	/* remove queued buffers from list */
	spin_lock_irqsave(q->irqlock, flags);
	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (NULL == q->bufs[i])
			continue;
		if (q->bufs[i]->state == VIDEOBUF_QUEUED) {
			list_del(&q->bufs[i]->queue);
			q->bufs[i]->state = VIDEOBUF_ERROR;
			wake_up_all(&q->bufs[i]->done);
		}
	}
	spin_unlock_irqrestore(q->irqlock, flags);

	/* free all buffers + clear queue */
	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (NULL == q->bufs[i])
			continue;
		q->ops->buf_release(q, q->bufs[i]);
	}
	INIT_LIST_HEAD(&q->stream);
}