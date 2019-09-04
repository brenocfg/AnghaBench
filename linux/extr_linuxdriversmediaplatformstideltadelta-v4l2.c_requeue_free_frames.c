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
struct vb2_v4l2_buffer {int dummy; } ;
struct delta_frame {scalar_t__ state; struct vb2_v4l2_buffer vbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {unsigned int nb_of_frames; TYPE_1__ fh; struct delta_frame** frames; } ;

/* Variables and functions */
 scalar_t__ DELTA_FRAME_FREE ; 
 scalar_t__ DELTA_FRAME_M2M ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (int /*<<< orphan*/ ,struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void requeue_free_frames(struct delta_ctx *ctx)
{
	struct vb2_v4l2_buffer *vbuf;
	struct delta_frame *frame;
	unsigned int i;

	/* requeue all free frames */
	for (i = 0; i < ctx->nb_of_frames; i++) {
		frame = ctx->frames[i];
		if (frame->state == DELTA_FRAME_FREE) {
			vbuf = &frame->vbuf;
			v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
			frame->state = DELTA_FRAME_M2M;
		}
	}
}