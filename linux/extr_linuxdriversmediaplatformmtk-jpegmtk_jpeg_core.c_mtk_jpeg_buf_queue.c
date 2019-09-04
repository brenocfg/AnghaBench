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
typedef  int /*<<< orphan*/  u8 ;
struct vb2_queue {int dummy; } ;
struct vb2_buffer {TYPE_2__* vb2_queue; int /*<<< orphan*/  index; } ;
struct mtk_jpeg_dec_param {int dummy; } ;
struct mtk_jpeg_src_buf {int flags; struct mtk_jpeg_dec_param dec_param; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {scalar_t__ state; TYPE_1__ fh; struct mtk_jpeg_dev* jpeg; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MTK_JPEG_BUF_FLAGS_LAST_FRAME ; 
 scalar_t__ MTK_JPEG_INIT ; 
 scalar_t__ MTK_JPEG_RUNNING ; 
 scalar_t__ MTK_JPEG_SOURCE_CHANGE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (struct mtk_jpeg_dec_param*,int /*<<< orphan*/ ,int) ; 
 int mtk_jpeg_parse (struct mtk_jpeg_dec_param*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_queue_src_chg_event (struct mtk_jpeg_ctx*) ; 
 int /*<<< orphan*/  mtk_jpeg_set_queue_data (struct mtk_jpeg_ctx*,struct mtk_jpeg_dec_param*) ; 
 struct mtk_jpeg_src_buf* mtk_jpeg_vb2_to_srcbuf (struct vb2_buffer*) ; 
 int /*<<< orphan*/  to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct mtk_jpeg_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 
 scalar_t__ vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_buf_queue(struct vb2_buffer *vb)
{
	struct mtk_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct mtk_jpeg_dec_param *param;
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	struct mtk_jpeg_src_buf *jpeg_src_buf;
	bool header_valid;

	v4l2_dbg(2, debug, &jpeg->v4l2_dev, "(%d) buf_q id=%d, vb=%p\n",
		 vb->vb2_queue->type, vb->index, vb);

	if (vb->vb2_queue->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		goto end;

	jpeg_src_buf = mtk_jpeg_vb2_to_srcbuf(vb);
	param = &jpeg_src_buf->dec_param;
	memset(param, 0, sizeof(*param));

	if (jpeg_src_buf->flags & MTK_JPEG_BUF_FLAGS_LAST_FRAME) {
		v4l2_dbg(1, debug, &jpeg->v4l2_dev, "Got eos\n");
		goto end;
	}
	header_valid = mtk_jpeg_parse(param, (u8 *)vb2_plane_vaddr(vb, 0),
				      vb2_get_plane_payload(vb, 0));
	if (!header_valid) {
		v4l2_err(&jpeg->v4l2_dev, "Header invalid.\n");
		vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
		return;
	}

	if (ctx->state == MTK_JPEG_INIT) {
		struct vb2_queue *dst_vq = v4l2_m2m_get_vq(
			ctx->fh.m2m_ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

		mtk_jpeg_queue_src_chg_event(ctx);
		mtk_jpeg_set_queue_data(ctx, param);
		ctx->state = vb2_is_streaming(dst_vq) ?
				MTK_JPEG_SOURCE_CHANGE : MTK_JPEG_RUNNING;
	}
end:
	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, to_vb2_v4l2_buffer(vb));
}