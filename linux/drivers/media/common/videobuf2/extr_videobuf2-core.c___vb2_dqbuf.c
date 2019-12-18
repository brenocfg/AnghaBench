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
struct vb2_queue {int dummy; } ;
struct vb2_buffer {scalar_t__ state; struct vb2_queue* vb2_queue; } ;

/* Variables and functions */
 scalar_t__ VB2_BUF_STATE_DEQUEUED ; 
 int /*<<< orphan*/  call_void_bufop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  init_buffer ; 

__attribute__((used)) static void __vb2_dqbuf(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;

	/* nothing to do if the buffer is already dequeued */
	if (vb->state == VB2_BUF_STATE_DEQUEUED)
		return;

	vb->state = VB2_BUF_STATE_DEQUEUED;

	call_void_bufop(q, init_buffer, vb);
}