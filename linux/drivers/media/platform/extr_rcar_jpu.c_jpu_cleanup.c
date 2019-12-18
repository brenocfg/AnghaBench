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
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_1__ fh; TYPE_2__* jpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCCMD ; 
 int /*<<< orphan*/  JCCMD_SRST ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  jpu_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jpu_cleanup(struct jpu_ctx *ctx, bool reset)
{
	/* remove current buffers and finish job */
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned long flags;

	spin_lock_irqsave(&ctx->jpu->lock, flags);

	src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_done(src_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_buf_done(dst_buf, VB2_BUF_STATE_ERROR);

	/* ...and give it a chance on next run */
	if (reset)
		jpu_write(ctx->jpu, JCCMD_SRST, JCCMD);

	spin_unlock_irqrestore(&ctx->jpu->lock, flags);

	v4l2_m2m_job_finish(ctx->jpu->m2m_dev, ctx->fh.m2m_ctx);
}