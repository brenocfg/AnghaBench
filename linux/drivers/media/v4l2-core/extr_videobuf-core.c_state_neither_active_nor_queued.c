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
struct videobuf_queue {int /*<<< orphan*/  irqlock; } ;
struct videobuf_buffer {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ VIDEOBUF_ACTIVE ; 
 scalar_t__ VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int state_neither_active_nor_queued(struct videobuf_queue *q,
					   struct videobuf_buffer *vb)
{
	unsigned long flags;
	bool rc;

	spin_lock_irqsave(q->irqlock, flags);
	rc = vb->state != VIDEOBUF_ACTIVE && vb->state != VIDEOBUF_QUEUED;
	spin_unlock_irqrestore(q->irqlock, flags);
	return rc;
}