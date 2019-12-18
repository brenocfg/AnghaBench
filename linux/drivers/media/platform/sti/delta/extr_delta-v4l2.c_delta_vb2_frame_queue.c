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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {int dummy; } ;
struct vb2_buffer {struct vb2_queue* vb2_queue; } ;
struct delta_frame {int dummy; } ;
struct delta_ctx {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DELTA_STATE_EOS ; 
 scalar_t__ DELTA_STATE_WF_EOS ; 
 int /*<<< orphan*/  delta_complete_eos (struct delta_ctx*,struct delta_frame*) ; 
 int /*<<< orphan*/  delta_recycle (struct delta_ctx*,struct delta_frame*) ; 
 struct delta_frame* to_frame (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct delta_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void delta_vb2_frame_queue(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	struct delta_ctx *ctx = vb2_get_drv_priv(q);
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct delta_frame *frame = to_frame(vbuf);

	if (ctx->state == DELTA_STATE_WF_EOS) {
		/* new frame available, EOS can now be completed */
		delta_complete_eos(ctx, frame);

		ctx->state = DELTA_STATE_EOS;

		/* return, no need to recycle this buffer to decoder */
		return;
	}

	/* recycle this frame */
	delta_recycle(ctx, frame);
}