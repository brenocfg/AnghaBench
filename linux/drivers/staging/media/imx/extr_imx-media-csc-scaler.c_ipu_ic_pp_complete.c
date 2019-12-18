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
struct vb2_v4l2_buffer {scalar_t__ sequence; } ;
struct ipu_image_convert_run {scalar_t__ status; } ;
struct ipu_csc_scaler_priv {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct ipu_csc_scaler_ctx {TYPE_1__ fh; int /*<<< orphan*/  sequence; struct ipu_csc_scaler_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  kfree (struct ipu_image_convert_run*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_copy_metadata (struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*,int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_ic_pp_complete(struct ipu_image_convert_run *run, void *_ctx)
{
	struct ipu_csc_scaler_ctx *ctx = _ctx;
	struct ipu_csc_scaler_priv *priv = ctx->priv;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, true);

	src_buf->sequence = ctx->sequence++;
	dst_buf->sequence = src_buf->sequence;

	v4l2_m2m_buf_done(src_buf, run->status ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);
	v4l2_m2m_buf_done(dst_buf, run->status ? VB2_BUF_STATE_ERROR :
						 VB2_BUF_STATE_DONE);

	v4l2_m2m_job_finish(priv->m2m_dev, ctx->fh.m2m_ctx);
	kfree(run);
}