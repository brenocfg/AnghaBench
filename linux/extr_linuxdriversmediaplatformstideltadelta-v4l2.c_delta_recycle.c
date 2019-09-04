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
struct delta_frame {scalar_t__ dts; scalar_t__ flags; int /*<<< orphan*/  state; struct vb2_v4l2_buffer vbuf; } ;
struct delta_dec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {TYPE_1__ fh; struct delta_dec* dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELTA_FRAME_FREE ; 
 int /*<<< orphan*/  DELTA_FRAME_M2M ; 
 int /*<<< orphan*/  DELTA_FRAME_OUT ; 
 int /*<<< orphan*/  call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*,struct delta_frame*) ; 
 int /*<<< orphan*/  recycle ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (int /*<<< orphan*/ ,struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static int delta_recycle(struct delta_ctx *ctx, struct delta_frame *frame)
{
	const struct delta_dec *dec = ctx->dec;

	/* recycle frame on decoder side */
	call_dec_op(dec, recycle, ctx, frame);

	/* this frame is no more output */
	frame->state &= ~DELTA_FRAME_OUT;

	/* requeue free frame */
	if (frame->state == DELTA_FRAME_FREE) {
		struct vb2_v4l2_buffer *vbuf = &frame->vbuf;

		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
		frame->state = DELTA_FRAME_M2M;
	}

	/* reset other frame fields */
	frame->flags = 0;
	frame->dts = 0;

	return 0;
}