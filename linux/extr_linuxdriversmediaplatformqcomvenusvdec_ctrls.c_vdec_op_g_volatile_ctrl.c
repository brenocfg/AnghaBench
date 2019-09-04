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
struct TYPE_4__ {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
union hfi_get_property {TYPE_2__ profile_level; } ;
typedef  int /*<<< orphan*/  u32 ;
struct vdec_controls {int /*<<< orphan*/  post_loop_deb_mode; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
struct TYPE_3__ {struct vdec_controls dec; } ;
struct venus_inst {int /*<<< orphan*/  num_output_bufs; TYPE_1__ controls; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT ; 
#define  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE 134 
#define  V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER 133 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 132 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 131 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 130 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 129 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 128 
 struct venus_inst* ctrl_to_inst (struct v4l2_ctrl*) ; 
 int hfi_session_get_property (struct venus_inst*,int /*<<< orphan*/ ,union hfi_get_property*) ; 

__attribute__((used)) static int vdec_op_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct venus_inst *inst = ctrl_to_inst(ctrl);
	struct vdec_controls *ctr = &inst->controls.dec;
	union hfi_get_property hprop;
	u32 ptype = HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT;
	int ret;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:
		ret = hfi_session_get_property(inst, ptype, &hprop);
		if (!ret)
			ctr->profile = hprop.profile_level.profile;
		ctrl->val = ctr->profile;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		ret = hfi_session_get_property(inst, ptype, &hprop);
		if (!ret)
			ctr->level = hprop.profile_level.level;
		ctrl->val = ctr->level;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctrl->val = ctr->post_loop_deb_mode;
		break;
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		ctrl->val = inst->num_output_bufs;
		break;
	default:
		return -EINVAL;
	};

	return 0;
}