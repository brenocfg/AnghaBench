#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_planes; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;
struct mtk_jpeg_src_buf {int flags; int /*<<< orphan*/  dec_param; } ;
struct mtk_jpeg_fb {int dummy; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  dec_reg_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {TYPE_1__ fh; int /*<<< orphan*/  state; struct mtk_jpeg_dev* jpeg; } ;
struct mtk_jpeg_bs {int dummy; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int MTK_JPEG_BUF_FLAGS_LAST_FRAME ; 
 int /*<<< orphan*/  MTK_JPEG_SOURCE_CHANGE ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 scalar_t__ mtk_jpeg_check_resolution_change (struct mtk_jpeg_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_jpeg_dec_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_dec_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_jpeg_bs*,struct mtk_jpeg_fb*) ; 
 int /*<<< orphan*/  mtk_jpeg_dec_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_queue_src_chg_event (struct mtk_jpeg_ctx*) ; 
 scalar_t__ mtk_jpeg_set_dec_dst (struct mtk_jpeg_ctx*,int /*<<< orphan*/ *,TYPE_2__*,struct mtk_jpeg_fb*) ; 
 int /*<<< orphan*/  mtk_jpeg_set_dec_src (struct mtk_jpeg_ctx*,TYPE_2__*,struct mtk_jpeg_bs*) ; 
 struct mtk_jpeg_src_buf* mtk_jpeg_vb2_to_srcbuf (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 int /*<<< orphan*/  v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_device_run(void *priv)
{
	struct mtk_jpeg_ctx *ctx = priv;
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	enum vb2_buffer_state buf_state = VB2_BUF_STATE_ERROR;
	unsigned long flags;
	struct mtk_jpeg_src_buf *jpeg_src_buf;
	struct mtk_jpeg_bs bs;
	struct mtk_jpeg_fb fb;
	int i;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(&src_buf->vb2_buf);

	if (jpeg_src_buf->flags & MTK_JPEG_BUF_FLAGS_LAST_FRAME) {
		for (i = 0; i < dst_buf->vb2_buf.num_planes; i++)
			vb2_set_plane_payload(&dst_buf->vb2_buf, i, 0);
		buf_state = VB2_BUF_STATE_DONE;
		goto dec_end;
	}

	if (mtk_jpeg_check_resolution_change(ctx, &jpeg_src_buf->dec_param)) {
		mtk_jpeg_queue_src_chg_event(ctx);
		ctx->state = MTK_JPEG_SOURCE_CHANGE;
		v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
		return;
	}

	mtk_jpeg_set_dec_src(ctx, &src_buf->vb2_buf, &bs);
	if (mtk_jpeg_set_dec_dst(ctx, &jpeg_src_buf->dec_param, &dst_buf->vb2_buf, &fb))
		goto dec_end;

	spin_lock_irqsave(&jpeg->hw_lock, flags);
	mtk_jpeg_dec_reset(jpeg->dec_reg_base);
	mtk_jpeg_dec_set_config(jpeg->dec_reg_base,
				&jpeg_src_buf->dec_param, &bs, &fb);

	mtk_jpeg_dec_start(jpeg->dec_reg_base);
	spin_unlock_irqrestore(&jpeg->hw_lock, flags);
	return;

dec_end:
	v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	v4l2_m2m_buf_done(src_buf, buf_state);
	v4l2_m2m_buf_done(dst_buf, buf_state);
	v4l2_m2m_job_finish(jpeg->m2m_dev, ctx->fh.m2m_ctx);
}