#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct venc_enc_param {int dummy; } ;
struct vb2_queue {int num_buffers; int /*<<< orphan*/  type; } ;
struct vb2_buffer {scalar_t__ state; } ;
struct TYPE_12__ {scalar_t__ seq_hdr_mode; } ;
struct mtk_vcodec_ctx {scalar_t__ state; int /*<<< orphan*/  id; TYPE_6__ enc_params; TYPE_5__* q_data; int /*<<< orphan*/  param_change; TYPE_3__* m2m_ctx; } ;
struct TYPE_11__ {TYPE_4__* fmt; } ;
struct TYPE_10__ {scalar_t__ fourcc; } ;
struct TYPE_8__ {int /*<<< orphan*/  q; } ;
struct TYPE_7__ {int /*<<< orphan*/  q; } ;
struct TYPE_9__ {TYPE_2__ out_q_ctx; TYPE_1__ cap_q_ctx; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_NONE ; 
 size_t MTK_Q_DATA_DST ; 
 scalar_t__ MTK_STATE_ABORT ; 
 scalar_t__ MTK_STATE_FREE ; 
 scalar_t__ MTK_STATE_HEADER ; 
 scalar_t__ V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ VB2_BUF_STATE_ACTIVE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  VENC_SET_PARAM_ENC ; 
 int /*<<< orphan*/  VENC_SET_PARAM_PREPEND_HEADER ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 
 int /*<<< orphan*/  mtk_venc_set_param (struct mtk_vcodec_ctx*,struct venc_enc_param*) ; 
 int /*<<< orphan*/  to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_buffer* vb2_get_buffer (struct vb2_queue*,int) ; 
 struct mtk_vcodec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_start_streaming_called (int /*<<< orphan*/ *) ; 
 int venc_if_set_param (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ,struct venc_enc_param*) ; 

__attribute__((used)) static int vb2ops_venc_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct mtk_vcodec_ctx *ctx = vb2_get_drv_priv(q);
	struct venc_enc_param param;
	int ret;
	int i;

	/* Once state turn into MTK_STATE_ABORT, we need stop_streaming
	  * to clear it
	  */
	if ((ctx->state == MTK_STATE_ABORT) || (ctx->state == MTK_STATE_FREE)) {
		ret = -EIO;
		goto err_set_param;
	}

	/* Do the initialization when both start_streaming have been called */
	if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		if (!vb2_start_streaming_called(&ctx->m2m_ctx->cap_q_ctx.q))
			return 0;
	} else {
		if (!vb2_start_streaming_called(&ctx->m2m_ctx->out_q_ctx.q))
			return 0;
	}

	mtk_venc_set_param(ctx, &param);
	ret = venc_if_set_param(ctx, VENC_SET_PARAM_ENC, &param);
	if (ret) {
		mtk_v4l2_err("venc_if_set_param failed=%d", ret);
		ctx->state = MTK_STATE_ABORT;
		goto err_set_param;
	}
	ctx->param_change = MTK_ENCODE_PARAM_NONE;

	if ((ctx->q_data[MTK_Q_DATA_DST].fmt->fourcc == V4L2_PIX_FMT_H264) &&
	    (ctx->enc_params.seq_hdr_mode !=
				V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE)) {
		ret = venc_if_set_param(ctx,
					VENC_SET_PARAM_PREPEND_HEADER,
					NULL);
		if (ret) {
			mtk_v4l2_err("venc_if_set_param failed=%d", ret);
			ctx->state = MTK_STATE_ABORT;
			goto err_set_param;
		}
		ctx->state = MTK_STATE_HEADER;
	}

	return 0;

err_set_param:
	for (i = 0; i < q->num_buffers; ++i) {
		struct vb2_buffer *buf = vb2_get_buffer(q, i);

		/*
		 * FIXME: This check is not needed as only active buffers
		 * can be marked as done.
		 */
		if (buf->state == VB2_BUF_STATE_ACTIVE) {
			mtk_v4l2_debug(0, "[%d] id=%d, type=%d, %d -> VB2_BUF_STATE_QUEUED",
					ctx->id, i, q->type,
					(int)buf->state);
			v4l2_m2m_buf_done(to_vb2_v4l2_buffer(buf),
					  VB2_BUF_STATE_QUEUED);
		}
	}

	return ret;
}