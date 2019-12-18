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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; scalar_t__ sequence; } ;
struct hantro_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  clocks; TYPE_1__* variant; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct hantro_ctx {int (* buf_finish ) (struct hantro_ctx*,int /*<<< orphan*/ *,unsigned int) ;TYPE_2__ fh; int /*<<< orphan*/  sequence_cap; int /*<<< orphan*/  sequence_out; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_3__ {int /*<<< orphan*/  num_clocks; } ;

/* Variables and functions */
 int VB2_BUF_STATE_ERROR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int stub1 (struct hantro_ctx*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hantro_job_finish(struct hantro_dev *vpu,
			      struct hantro_ctx *ctx,
			      unsigned int bytesused,
			      enum vb2_buffer_state result)
{
	struct vb2_v4l2_buffer *src, *dst;
	int ret;

	pm_runtime_mark_last_busy(vpu->dev);
	pm_runtime_put_autosuspend(vpu->dev);
	clk_bulk_disable(vpu->variant->num_clocks, vpu->clocks);

	src = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

	if (WARN_ON(!src))
		return;
	if (WARN_ON(!dst))
		return;

	src->sequence = ctx->sequence_out++;
	dst->sequence = ctx->sequence_cap++;

	ret = ctx->buf_finish(ctx, &dst->vb2_buf, bytesused);
	if (ret)
		result = VB2_BUF_STATE_ERROR;

	v4l2_m2m_buf_done(src, result);
	v4l2_m2m_buf_done(dst, result);

	v4l2_m2m_job_finish(vpu->m2m_dev, ctx->fh.m2m_ctx);
}