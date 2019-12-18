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
struct vdec_controls {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  post_loop_deb_mode; } ;
struct TYPE_2__ {struct vdec_controls dec; } ;
struct venus_inst {TYPE_1__ controls; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER 133 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 132 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 131 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 130 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 129 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 128 
 struct venus_inst* ctrl_to_inst (struct v4l2_ctrl*) ; 

__attribute__((used)) static int vdec_op_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct venus_inst *inst = ctrl_to_inst(ctrl);
	struct vdec_controls *ctr = &inst->controls.dec;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctr->post_loop_deb_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:
		ctr->profile = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		ctr->level = ctrl->val;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}