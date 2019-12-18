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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct mtk_jpeg_src_buf {int /*<<< orphan*/  dec_param; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {scalar_t__ state; TYPE_2__* jpeg; TYPE_1__ fh; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MTK_JPEG_INIT ; 
 scalar_t__ MTK_JPEG_RUNNING ; 
 scalar_t__ MTK_JPEG_SOURCE_CHANGE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 struct vb2_v4l2_buffer* mtk_jpeg_buf_remove (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_set_queue_data (struct mtk_jpeg_ctx*,int /*<<< orphan*/ *) ; 
 struct mtk_jpeg_src_buf* mtk_jpeg_vb2_to_srcbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 struct mtk_jpeg_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void mtk_jpeg_stop_streaming(struct vb2_queue *q)
{
	struct mtk_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	struct vb2_v4l2_buffer *vb;

	/*
	 * STREAMOFF is an acknowledgment for source change event.
	 * Before STREAMOFF, we still have to return the old resolution and
	 * subsampling. Update capture queue when the stream is off.
	 */
	if (ctx->state == MTK_JPEG_SOURCE_CHANGE &&
	    !V4L2_TYPE_IS_OUTPUT(q->type)) {
		struct mtk_jpeg_src_buf *src_buf;

		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		src_buf = mtk_jpeg_vb2_to_srcbuf(&vb->vb2_buf);
		mtk_jpeg_set_queue_data(ctx, &src_buf->dec_param);
		ctx->state = MTK_JPEG_RUNNING;
	} else if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		ctx->state = MTK_JPEG_INIT;
	}

	while ((vb = mtk_jpeg_buf_remove(ctx, q->type)))
		v4l2_m2m_buf_done(vb, VB2_BUF_STATE_ERROR);

	pm_runtime_put_sync(ctx->jpeg->dev);
}