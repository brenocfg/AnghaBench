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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_2__* jpu; TYPE_1__ fh; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct jpu_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void jpu_stop_streaming(struct vb2_queue *vq)
{
	struct jpu_ctx *ctx = vb2_get_drv_priv(vq);
	struct vb2_v4l2_buffer *vb;
	unsigned long flags;

	for (;;) {
		if (V4L2_TYPE_IS_OUTPUT(vq->type))
			vb = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		else
			vb = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
		if (vb == NULL)
			return;
		spin_lock_irqsave(&ctx->jpu->lock, flags);
		v4l2_m2m_buf_done(vb, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->jpu->lock, flags);
	}
}