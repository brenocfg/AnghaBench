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
struct vb2_queue {unsigned int num_buffers; struct vb2_buffer** bufs; int /*<<< orphan*/  done_wq; int /*<<< orphan*/  owned_by_drv_count; int /*<<< orphan*/  done_list; int /*<<< orphan*/  queued_list; scalar_t__ error; scalar_t__ queued_count; scalar_t__ start_streaming_called; scalar_t__ streaming; } ;
struct vb2_buffer {scalar_t__ state; unsigned int num_planes; TYPE_1__* planes; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ VB2_BUF_STATE_ACTIVE ; 
 scalar_t__ VB2_BUF_STATE_DEQUEUED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 scalar_t__ VB2_BUF_STATE_PREPARED ; 
 scalar_t__ VB2_BUF_STATE_QUEUED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vb2_dqbuf (struct vb2_buffer*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_finish ; 
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_void_qop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_queue*) ; 
 int /*<<< orphan*/  call_void_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  pr_warn (char*,struct vb2_buffer*) ; 
 int /*<<< orphan*/  stop_streaming ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vb2_queue_cancel(struct vb2_queue *q)
{
	unsigned int i;

	/*
	 * Tell driver to stop all transactions and release all queued
	 * buffers.
	 */
	if (q->start_streaming_called)
		call_void_qop(q, stop_streaming, q);

	/*
	 * If you see this warning, then the driver isn't cleaning up properly
	 * in stop_streaming(). See the stop_streaming() documentation in
	 * videobuf2-core.h for more information how buffers should be returned
	 * to vb2 in stop_streaming().
	 */
	if (WARN_ON(atomic_read(&q->owned_by_drv_count))) {
		for (i = 0; i < q->num_buffers; ++i)
			if (q->bufs[i]->state == VB2_BUF_STATE_ACTIVE) {
				pr_warn("driver bug: stop_streaming operation is leaving buf %p in active state\n",
					q->bufs[i]);
				vb2_buffer_done(q->bufs[i], VB2_BUF_STATE_ERROR);
			}
		/* Must be zero now */
		WARN_ON(atomic_read(&q->owned_by_drv_count));
	}

	q->streaming = 0;
	q->start_streaming_called = 0;
	q->queued_count = 0;
	q->error = 0;

	/*
	 * Remove all buffers from videobuf's list...
	 */
	INIT_LIST_HEAD(&q->queued_list);
	/*
	 * ...and done list; userspace will not receive any buffers it
	 * has not already dequeued before initiating cancel.
	 */
	INIT_LIST_HEAD(&q->done_list);
	atomic_set(&q->owned_by_drv_count, 0);
	wake_up_all(&q->done_wq);

	/*
	 * Reinitialize all buffers for next use.
	 * Make sure to call buf_finish for any queued buffers. Normally
	 * that's done in dqbuf, but that's not going to happen when we
	 * cancel the whole queue. Note: this code belongs here, not in
	 * __vb2_dqbuf() since in vb2_core_dqbuf() there is a critical
	 * call to __fill_user_buffer() after buf_finish(). That order can't
	 * be changed, so we can't move the buf_finish() to __vb2_dqbuf().
	 */
	for (i = 0; i < q->num_buffers; ++i) {
		struct vb2_buffer *vb = q->bufs[i];

		if (vb->state == VB2_BUF_STATE_PREPARED ||
		    vb->state == VB2_BUF_STATE_QUEUED) {
			unsigned int plane;

			for (plane = 0; plane < vb->num_planes; ++plane)
				call_void_memop(vb, finish,
						vb->planes[plane].mem_priv);
		}

		if (vb->state != VB2_BUF_STATE_DEQUEUED) {
			vb->state = VB2_BUF_STATE_PREPARED;
			call_void_vb_qop(vb, buf_finish, vb);
		}
		__vb2_dqbuf(vb);
	}
}