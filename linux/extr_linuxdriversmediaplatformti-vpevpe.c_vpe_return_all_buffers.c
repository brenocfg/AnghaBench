#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {TYPE_2__* dev; struct vb2_v4l2_buffer* dst_vb; struct vb2_v4l2_buffer** src_vbs; TYPE_1__ fh; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpe_return_all_buffers(struct vpe_ctx *ctx,  struct vb2_queue *q,
				   enum vb2_buffer_state state)
{
	struct vb2_v4l2_buffer *vb;
	unsigned long flags;

	for (;;) {
		if (V4L2_TYPE_IS_OUTPUT(q->type))
			vb = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		else
			vb = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
		if (!vb)
			break;
		spin_lock_irqsave(&ctx->dev->lock, flags);
		v4l2_m2m_buf_done(vb, state);
		spin_unlock_irqrestore(&ctx->dev->lock, flags);
	}

	/*
	 * Cleanup the in-transit vb2 buffers that have been
	 * removed from their respective queue already but for
	 * which procecessing has not been completed yet.
	 */
	if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		spin_lock_irqsave(&ctx->dev->lock, flags);

		if (ctx->src_vbs[2])
			v4l2_m2m_buf_done(ctx->src_vbs[2], state);

		if (ctx->src_vbs[1] && (ctx->src_vbs[1] != ctx->src_vbs[2]))
			v4l2_m2m_buf_done(ctx->src_vbs[1], state);

		if (ctx->src_vbs[0] &&
		    (ctx->src_vbs[0] != ctx->src_vbs[1]) &&
		    (ctx->src_vbs[0] != ctx->src_vbs[2]))
			v4l2_m2m_buf_done(ctx->src_vbs[0], state);

		ctx->src_vbs[2] = NULL;
		ctx->src_vbs[1] = NULL;
		ctx->src_vbs[0] = NULL;

		spin_unlock_irqrestore(&ctx->dev->lock, flags);
	} else {
		if (ctx->dst_vb) {
			spin_lock_irqsave(&ctx->dev->lock, flags);

			v4l2_m2m_buf_done(ctx->dst_vb, state);
			ctx->dst_vb = NULL;
			spin_unlock_irqrestore(&ctx->dev->lock, flags);
		}
	}
}