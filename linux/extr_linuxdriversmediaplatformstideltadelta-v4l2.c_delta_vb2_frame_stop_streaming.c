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
struct delta_frame {int state; struct vb2_v4l2_buffer vbuf; } ;
struct delta_dec {int dummy; } ;
struct delta_ctx {unsigned int nb_of_frames; int aborting; scalar_t__ frame_num; struct delta_frame** frames; struct delta_dec* dec; } ;

/* Variables and functions */
 int DELTA_FRAME_OUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  call_dec_op (struct delta_dec const*,int /*<<< orphan*/ ,struct delta_ctx*) ; 
 int /*<<< orphan*/  delta_flush_dts (struct delta_ctx*) ; 
 int /*<<< orphan*/  flush ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct delta_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void delta_vb2_frame_stop_streaming(struct vb2_queue *q)
{
	struct delta_ctx *ctx = vb2_get_drv_priv(q);
	struct vb2_v4l2_buffer *vbuf;
	struct delta_frame *frame;
	const struct delta_dec *dec = ctx->dec;
	unsigned int i;

	delta_flush_dts(ctx);

	call_dec_op(dec, flush, ctx);

	/*
	 * return all buffers to vb2 in ERROR state
	 * & reset each frame state to OUT
	 */
	for (i = 0; i < ctx->nb_of_frames; i++) {
		frame = ctx->frames[i];
		if (!(frame->state & DELTA_FRAME_OUT)) {
			vbuf = &frame->vbuf;
			v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_ERROR);
		}
		frame->state = DELTA_FRAME_OUT;
	}

	ctx->frame_num = 0;

	ctx->aborting = false;
}