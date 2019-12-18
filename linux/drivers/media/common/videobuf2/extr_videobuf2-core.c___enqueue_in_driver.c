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
struct vb2_queue {int /*<<< orphan*/  owned_by_drv_count; } ;
struct vb2_buffer {int /*<<< orphan*/  state; struct vb2_queue* vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ACTIVE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_queue ; 
 int /*<<< orphan*/  call_void_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  trace_vb2_buf_queue (struct vb2_queue*,struct vb2_buffer*) ; 

__attribute__((used)) static void __enqueue_in_driver(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;

	vb->state = VB2_BUF_STATE_ACTIVE;
	atomic_inc(&q->owned_by_drv_count);

	trace_vb2_buf_queue(q, vb);

	call_void_vb_qop(vb, buf_queue, vb);
}