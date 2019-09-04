#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int error; } ;
struct venus_inst {TYPE_1__ ctrl_handler; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VP8_PROFILE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_VOLATILE ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_5_1 ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_0 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE ; 
 int V4L2_MPEG_VIDEO_VP8_PROFILE_0 ; 
 int V4L2_MPEG_VIDEO_VP8_PROFILE_3 ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_1__*) ; 
 int v4l2_ctrl_handler_init (TYPE_1__*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std_menu (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vdec_ctrl_ops ; 

int vdec_ctrl_init(struct venus_inst *inst)
{
	struct v4l2_ctrl *ctrl;
	int ret;

	ret = v4l2_ctrl_handler_init(&inst->ctrl_handler, 7);
	if (ret)
		return ret;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE) |
		  (1 << V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE)),
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
				      V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
				      0, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROFILE,
		V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_H264_LEVEL,
				      V4L2_MPEG_VIDEO_H264_LEVEL_5_1,
				      0, V4L2_MPEG_VIDEO_H264_LEVEL_1_0);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_VP8_PROFILE,
				      V4L2_MPEG_VIDEO_VP8_PROFILE_3,
				      0, V4L2_MPEG_VIDEO_VP8_PROFILE_0);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER, 0, 1, 1, 0);

	ctrl = v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MIN_BUFFERS_FOR_CAPTURE, 1, 32, 1, 1);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ret = inst->ctrl_handler.error;
	if (ret) {
		v4l2_ctrl_handler_free(&inst->ctrl_handler);
		return ret;
	}

	return 0;
}