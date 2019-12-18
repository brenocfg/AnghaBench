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
struct vb2_queue {unsigned int type; int waiting_for_buffers; int last_buffer_dequeued; int /*<<< orphan*/  is_output; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __vb2_queue_cancel (struct vb2_queue*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

int vb2_core_streamoff(struct vb2_queue *q, unsigned int type)
{
	if (type != q->type) {
		dprintk(1, "invalid stream type\n");
		return -EINVAL;
	}

	/*
	 * Cancel will pause streaming and remove all buffers from the driver
	 * and videobuf, effectively returning control over them to userspace.
	 *
	 * Note that we do this even if q->streaming == 0: if you prepare or
	 * queue buffers, and then call streamoff without ever having called
	 * streamon, you would still expect those buffers to be returned to
	 * their normal dequeued state.
	 */
	__vb2_queue_cancel(q);
	q->waiting_for_buffers = !q->is_output;
	q->last_buffer_dequeued = false;

	dprintk(3, "successful\n");
	return 0;
}