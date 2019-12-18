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
struct venc_enc_param {int frm_rate; int /*<<< orphan*/  intra_period; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  buf_height; int /*<<< orphan*/  buf_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  h264_level; int /*<<< orphan*/  h264_profile; int /*<<< orphan*/  input_yuv_fmt; } ;
struct mtk_enc_params {int framerate_num; int framerate_denom; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  intra_period; int /*<<< orphan*/  h264_level; int /*<<< orphan*/  h264_profile; } ;
struct mtk_vcodec_ctx {struct mtk_enc_params enc_params; struct mtk_q_data* q_data; } ;
struct mtk_q_data {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  visible_height; int /*<<< orphan*/  visible_width; TYPE_1__* fmt; } ;
struct TYPE_2__ {int fourcc; } ;

/* Variables and functions */
 size_t MTK_Q_DATA_SRC ; 
#define  V4L2_PIX_FMT_NV12M 131 
#define  V4L2_PIX_FMT_NV21M 130 
#define  V4L2_PIX_FMT_YUV420M 129 
#define  V4L2_PIX_FMT_YVU420M 128 
 int /*<<< orphan*/  VENC_YUV_FORMAT_I420 ; 
 int /*<<< orphan*/  VENC_YUV_FORMAT_NV12 ; 
 int /*<<< orphan*/  VENC_YUV_FORMAT_NV21 ; 
 int /*<<< orphan*/  VENC_YUV_FORMAT_YV12 ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 

__attribute__((used)) static void mtk_venc_set_param(struct mtk_vcodec_ctx *ctx,
				struct venc_enc_param *param)
{
	struct mtk_q_data *q_data_src = &ctx->q_data[MTK_Q_DATA_SRC];
	struct mtk_enc_params *enc_params = &ctx->enc_params;

	switch (q_data_src->fmt->fourcc) {
	case V4L2_PIX_FMT_YUV420M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_I420;
		break;
	case V4L2_PIX_FMT_YVU420M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_YV12;
		break;
	case V4L2_PIX_FMT_NV12M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_NV12;
		break;
	case V4L2_PIX_FMT_NV21M:
		param->input_yuv_fmt = VENC_YUV_FORMAT_NV21;
		break;
	default:
		mtk_v4l2_err("Unsupported fourcc =%d", q_data_src->fmt->fourcc);
		break;
	}
	param->h264_profile = enc_params->h264_profile;
	param->h264_level = enc_params->h264_level;

	/* Config visible resolution */
	param->width = q_data_src->visible_width;
	param->height = q_data_src->visible_height;
	/* Config coded resolution */
	param->buf_width = q_data_src->coded_width;
	param->buf_height = q_data_src->coded_height;
	param->frm_rate = enc_params->framerate_num /
			enc_params->framerate_denom;
	param->intra_period = enc_params->intra_period;
	param->gop_size = enc_params->gop_size;
	param->bitrate = enc_params->bitrate;

	mtk_v4l2_debug(0,
		"fmt 0x%x, P/L %d/%d, w/h %d/%d, buf %d/%d, fps/bps %d/%d, gop %d, i_period %d",
		param->input_yuv_fmt, param->h264_profile,
		param->h264_level, param->width, param->height,
		param->buf_width, param->buf_height,
		param->frm_rate, param->bitrate,
		param->gop_size, param->intra_period);
}