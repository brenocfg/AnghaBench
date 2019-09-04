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
struct vb2_queue {int dummy; } ;
struct v4l2_decoder_cmd {int cmd; } ;
struct mtk_vcodec_ctx {int /*<<< orphan*/  m2m_ctx; TYPE_1__* empty_flush_buf; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
#define  V4L2_DEC_CMD_START 129 
#define  V4L2_DEC_CMD_STOP 128 
 struct mtk_vcodec_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int,char*,...) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_try_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_clear_last_buffer_dequeued (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_is_streaming (struct vb2_queue*) ; 
 int vidioc_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 

__attribute__((used)) static int vidioc_decoder_cmd(struct file *file, void *priv,
				struct v4l2_decoder_cmd *cmd)
{
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	struct vb2_queue *src_vq, *dst_vq;
	int ret;

	ret = vidioc_try_decoder_cmd(file, priv, cmd);
	if (ret)
		return ret;

	mtk_v4l2_debug(1, "decoder cmd=%u", cmd->cmd);
	dst_vq = v4l2_m2m_get_vq(ctx->m2m_ctx,
				V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	switch (cmd->cmd) {
	case V4L2_DEC_CMD_STOP:
		src_vq = v4l2_m2m_get_vq(ctx->m2m_ctx,
				V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
		if (!vb2_is_streaming(src_vq)) {
			mtk_v4l2_debug(1, "Output stream is off. No need to flush.");
			return 0;
		}
		if (!vb2_is_streaming(dst_vq)) {
			mtk_v4l2_debug(1, "Capture stream is off. No need to flush.");
			return 0;
		}
		v4l2_m2m_buf_queue(ctx->m2m_ctx, &ctx->empty_flush_buf->vb);
		v4l2_m2m_try_schedule(ctx->m2m_ctx);
		break;

	case V4L2_DEC_CMD_START:
		vb2_clear_last_buffer_dequeued(dst_vq);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}