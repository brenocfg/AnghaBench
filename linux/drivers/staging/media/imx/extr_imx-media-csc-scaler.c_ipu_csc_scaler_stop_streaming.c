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
struct vb2_queue {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct ipu_csc_scaler_ctx {TYPE_1__ fh; scalar_t__ sequence; int /*<<< orphan*/ * icc; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  ipu_image_convert_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct ipu_csc_scaler_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void ipu_csc_scaler_stop_streaming(struct vb2_queue *q)
{
	struct ipu_csc_scaler_ctx *ctx = vb2_get_drv_priv(q);
	struct vb2_v4l2_buffer *buf;

	if (ctx->icc) {
		ipu_image_convert_unprepare(ctx->icc);
		ctx->icc = NULL;
	}

	ctx->sequence = 0;

	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		while ((buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_done(buf, VB2_BUF_STATE_ERROR);
	} else {
		while ((buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx)))
			v4l2_m2m_buf_done(buf, VB2_BUF_STATE_ERROR);
	}
}