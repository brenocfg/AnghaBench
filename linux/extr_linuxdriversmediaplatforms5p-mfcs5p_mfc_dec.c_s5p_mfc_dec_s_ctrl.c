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
struct s5p_mfc_ctx {int /*<<< orphan*/  slice_interface; int /*<<< orphan*/  loop_filter_mpeg4; int /*<<< orphan*/  display_delay_enable; int /*<<< orphan*/  display_delay; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY 131 
#define  V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE 130 
#define  V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER 129 
#define  V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE 128 
 struct s5p_mfc_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  mfc_err (char*,int) ; 

__attribute__((used)) static int s5p_mfc_dec_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
		ctx->display_delay = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE:
		ctx->display_delay_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctx->loop_filter_mpeg4 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
		ctx->slice_interface = ctrl->val;
		break;
	default:
		mfc_err("Invalid control 0x%08x\n", ctrl->id);
		return -EINVAL;
	}
	return 0;
}