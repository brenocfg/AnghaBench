#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/  done_wq; int /*<<< orphan*/  done_lock; int /*<<< orphan*/  owned_by_drv_count; int /*<<< orphan*/  done_list; } ;
struct TYPE_5__ {scalar_t__ req; } ;
struct vb2_buffer {scalar_t__ state; unsigned int num_planes; TYPE_2__ req_obj; int /*<<< orphan*/  done_entry; scalar_t__ synced; TYPE_1__* planes; int /*<<< orphan*/  index; int /*<<< orphan*/  cnt_buf_done; struct vb2_queue* vb2_queue; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_4__ {int /*<<< orphan*/  mem_priv; } ;

/* Variables and functions */
 scalar_t__ VB2_BUF_STATE_ACTIVE ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
#define  VB2_BUF_STATE_QUEUED 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_request_object_put (TYPE_2__*) ; 
 int /*<<< orphan*/  media_request_object_unbind (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vb2_buf_done (struct vb2_queue*,struct vb2_buffer*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void vb2_buffer_done(struct vb2_buffer *vb, enum vb2_buffer_state state)
{
	struct vb2_queue *q = vb->vb2_queue;
	unsigned long flags;
	unsigned int plane;

	if (WARN_ON(vb->state != VB2_BUF_STATE_ACTIVE))
		return;

	if (WARN_ON(state != VB2_BUF_STATE_DONE &&
		    state != VB2_BUF_STATE_ERROR &&
		    state != VB2_BUF_STATE_QUEUED))
		state = VB2_BUF_STATE_ERROR;

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Although this is not a callback, it still does have to balance
	 * with the buf_queue op. So update this counter manually.
	 */
	vb->cnt_buf_done++;
#endif
	dprintk(4, "done processing on buffer %d, state: %d\n",
			vb->index, state);

	if (state != VB2_BUF_STATE_QUEUED) {
		/* sync buffers */
		for (plane = 0; plane < vb->num_planes; ++plane)
			call_void_memop(vb, finish, vb->planes[plane].mem_priv);
		vb->synced = 0;
	}

	spin_lock_irqsave(&q->done_lock, flags);
	if (state == VB2_BUF_STATE_QUEUED) {
		vb->state = VB2_BUF_STATE_QUEUED;
	} else {
		/* Add the buffer to the done buffers list */
		list_add_tail(&vb->done_entry, &q->done_list);
		vb->state = state;
	}
	atomic_dec(&q->owned_by_drv_count);

	if (state != VB2_BUF_STATE_QUEUED && vb->req_obj.req) {
		media_request_object_unbind(&vb->req_obj);
		media_request_object_put(&vb->req_obj);
	}

	spin_unlock_irqrestore(&q->done_lock, flags);

	trace_vb2_buf_done(q, vb);

	switch (state) {
	case VB2_BUF_STATE_QUEUED:
		return;
	default:
		/* Inform any processes that may be waiting for buffers */
		wake_up(&q->done_wq);
		break;
	}
}