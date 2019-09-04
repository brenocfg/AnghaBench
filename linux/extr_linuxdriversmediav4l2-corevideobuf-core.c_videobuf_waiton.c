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
struct videobuf_queue {scalar_t__ ext_lock; } ;
struct videobuf_buffer {int /*<<< orphan*/  done; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MAGIC_BUFFER ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_is_locked (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 scalar_t__ state_neither_active_nor_queued (struct videobuf_queue*,struct videobuf_buffer*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,scalar_t__) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

int videobuf_waiton(struct videobuf_queue *q, struct videobuf_buffer *vb,
		int non_blocking, int intr)
{
	bool is_ext_locked;
	int ret = 0;

	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);

	if (non_blocking) {
		if (state_neither_active_nor_queued(q, vb))
			return 0;
		return -EAGAIN;
	}

	is_ext_locked = q->ext_lock && mutex_is_locked(q->ext_lock);

	/* Release vdev lock to prevent this wait from blocking outside access to
	   the device. */
	if (is_ext_locked)
		mutex_unlock(q->ext_lock);
	if (intr)
		ret = wait_event_interruptible(vb->done,
					state_neither_active_nor_queued(q, vb));
	else
		wait_event(vb->done, state_neither_active_nor_queued(q, vb));
	/* Relock */
	if (is_ext_locked)
		mutex_lock(q->ext_lock);

	return ret;
}