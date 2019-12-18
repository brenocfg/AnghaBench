#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct mtk_enc_params {int force_intra; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  intra_period; int /*<<< orphan*/  h264_level; int /*<<< orphan*/  h264_profile; int /*<<< orphan*/  rc_mb; int /*<<< orphan*/  seq_hdr_mode; int /*<<< orphan*/  h264_max_qp; int /*<<< orphan*/  rc_frame; int /*<<< orphan*/  num_b_frame; int /*<<< orphan*/  bitrate; } ;
struct mtk_vcodec_ctx {int /*<<< orphan*/  param_change; struct mtk_enc_params enc_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_BITRATE ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_FORCE_INTRA ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_GOP_SIZE ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_INTRA_PERIOD ; 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 138 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 137 
#define  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME 136 
#define  V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE 135 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 134 
#define  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD 133 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 132 
#define  V4L2_CID_MPEG_VIDEO_H264_MAX_QP 131 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 130 
#define  V4L2_CID_MPEG_VIDEO_HEADER_MODE 129 
#define  V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE 128 
 struct mtk_vcodec_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int,char*,...) ; 

__attribute__((used)) static int vidioc_venc_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct mtk_vcodec_ctx *ctx = ctrl_to_ctx(ctrl);
	struct mtk_enc_params *p = &ctx->enc_params;
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_BITRATE val = %d",
			       ctrl->val);
		p->bitrate = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_BITRATE;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_B_FRAMES val = %d",
			       ctrl->val);
		p->num_b_frame = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE val = %d",
			       ctrl->val);
		p->rc_frame = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_MAX_QP val = %d",
			       ctrl->val);
		p->h264_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_HEADER_MODE val = %d",
			       ctrl->val);
		p->seq_hdr_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE val = %d",
			       ctrl->val);
		p->rc_mb = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_PROFILE val = %d",
			       ctrl->val);
		p->h264_profile = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_LEVEL val = %d",
			       ctrl->val);
		p->h264_level = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_H264_I_PERIOD val = %d",
			       ctrl->val);
		p->intra_period = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_INTRA_PERIOD;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_GOP_SIZE val = %d",
			       ctrl->val);
		p->gop_size = ctrl->val;
		ctx->param_change |= MTK_ENCODE_PARAM_GOP_SIZE;
		break;
	case V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		mtk_v4l2_debug(2, "V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME");
		p->force_intra = 1;
		ctx->param_change |= MTK_ENCODE_PARAM_FORCE_INTRA;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}