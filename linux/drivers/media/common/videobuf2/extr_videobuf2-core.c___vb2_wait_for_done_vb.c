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
struct vb2_queue {int waiting_in_dqbuf; scalar_t__ error; int /*<<< orphan*/  streaming; int /*<<< orphan*/  done_list; int /*<<< orphan*/  done_wq; scalar_t__ last_buffer_dequeued; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EPIPE ; 
 int /*<<< orphan*/  call_void_qop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_queue*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_finish ; 
 int /*<<< orphan*/  wait_prepare ; 

__attribute__((used)) static int __vb2_wait_for_done_vb(struct vb2_queue *q, int nonblocking)
{
	/*
	 * All operations on vb_done_list are performed under done_lock
	 * spinlock protection. However, buffers may be removed from
	 * it and returned to userspace only while holding both driver's
	 * lock and the done_lock spinlock. Thus we can be sure that as
	 * long as we hold the driver's lock, the list will remain not
	 * empty if list_empty() check succeeds.
	 */

	for (;;) {
		int ret;

		if (q->waiting_in_dqbuf) {
			dprintk(1, "another dup()ped fd is waiting for a buffer\n");
			return -EBUSY;
		}

		if (!q->streaming) {
			dprintk(1, "streaming off, will not wait for buffers\n");
			return -EINVAL;
		}

		if (q->error) {
			dprintk(1, "Queue in error state, will not wait for buffers\n");
			return -EIO;
		}

		if (q->last_buffer_dequeued) {
			dprintk(3, "last buffer dequeued already, will not wait for buffers\n");
			return -EPIPE;
		}

		if (!list_empty(&q->done_list)) {
			/*
			 * Found a buffer that we were waiting for.
			 */
			break;
		}

		if (nonblocking) {
			dprintk(3, "nonblocking and no buffers to dequeue, will not wait\n");
			return -EAGAIN;
		}

		q->waiting_in_dqbuf = 1;
		/*
		 * We are streaming and blocking, wait for another buffer to
		 * become ready or for streamoff. Driver's lock is released to
		 * allow streamoff or qbuf to be called while waiting.
		 */
		call_void_qop(q, wait_prepare, q);

		/*
		 * All locks have been released, it is safe to sleep now.
		 */
		dprintk(3, "will sleep waiting for buffers\n");
		ret = wait_event_interruptible(q->done_wq,
				!list_empty(&q->done_list) || !q->streaming ||
				q->error);

		/*
		 * We need to reevaluate both conditions again after reacquiring
		 * the locks or return an error if one occurred.
		 */
		call_void_qop(q, wait_finish, q);
		q->waiting_in_dqbuf = 0;
		if (ret) {
			dprintk(1, "sleep was interrupted\n");
			return ret;
		}
	}
	return 0;
}