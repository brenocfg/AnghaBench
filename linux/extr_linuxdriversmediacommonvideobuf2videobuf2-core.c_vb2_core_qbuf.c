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
struct vb2_queue {scalar_t__ queued_count; int waiting_for_buffers; scalar_t__ min_buffers_needed; scalar_t__ start_streaming_called; scalar_t__ streaming; int /*<<< orphan*/  queued_list; struct vb2_buffer** bufs; scalar_t__ error; } ;
struct vb2_buffer {int state; int index; int /*<<< orphan*/  queued_entry; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  VB2_BUF_STATE_DEQUEUED 130 
#define  VB2_BUF_STATE_PREPARED 129 
#define  VB2_BUF_STATE_PREPARING 128 
 int VB2_BUF_STATE_QUEUED ; 
 int __buf_prepare (struct vb2_buffer*,void*) ; 
 int /*<<< orphan*/  __enqueue_in_driver (struct vb2_buffer*) ; 
 int /*<<< orphan*/  call_void_bufop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_buffer*,void*) ; 
 int /*<<< orphan*/  copy_timestamp ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  fill_user_buffer ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_vb2_qbuf (struct vb2_queue*,struct vb2_buffer*) ; 
 int vb2_start_streaming (struct vb2_queue*) ; 

int vb2_core_qbuf(struct vb2_queue *q, unsigned int index, void *pb)
{
	struct vb2_buffer *vb;
	int ret;

	if (q->error) {
		dprintk(1, "fatal error occurred on queue\n");
		return -EIO;
	}

	vb = q->bufs[index];

	switch (vb->state) {
	case VB2_BUF_STATE_DEQUEUED:
		ret = __buf_prepare(vb, pb);
		if (ret)
			return ret;
		break;
	case VB2_BUF_STATE_PREPARED:
		break;
	case VB2_BUF_STATE_PREPARING:
		dprintk(1, "buffer still being prepared\n");
		return -EINVAL;
	default:
		dprintk(1, "invalid buffer state %d\n", vb->state);
		return -EINVAL;
	}

	/*
	 * Add to the queued buffers list, a buffer will stay on it until
	 * dequeued in dqbuf.
	 */
	list_add_tail(&vb->queued_entry, &q->queued_list);
	q->queued_count++;
	q->waiting_for_buffers = false;
	vb->state = VB2_BUF_STATE_QUEUED;

	if (pb)
		call_void_bufop(q, copy_timestamp, vb, pb);

	trace_vb2_qbuf(q, vb);

	/*
	 * If already streaming, give the buffer to driver for processing.
	 * If not, the buffer will be given to driver on next streamon.
	 */
	if (q->start_streaming_called)
		__enqueue_in_driver(vb);

	/* Fill buffer information for the userspace */
	if (pb)
		call_void_bufop(q, fill_user_buffer, vb, pb);

	/*
	 * If streamon has been called, and we haven't yet called
	 * start_streaming() since not enough buffers were queued, and
	 * we now have reached the minimum number of queued buffers,
	 * then we can finally call start_streaming().
	 */
	if (q->streaming && !q->start_streaming_called &&
	    q->queued_count >= q->min_buffers_needed) {
		ret = vb2_start_streaming(q);
		if (ret)
			return ret;
	}

	dprintk(2, "qbuf of buffer %d succeeded\n", vb->index);
	return 0;
}