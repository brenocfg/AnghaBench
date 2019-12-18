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
struct v4l2_ctrl {scalar_t__ id; int val; } ;
struct mmal_parameter_video_profile {int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct TYPE_3__ {int enc_profile; int enc_level; } ;
struct bm2835_mmal_dev {TYPE_2__** component; int /*<<< orphan*/  instance; TYPE_1__ capture; } ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_4__ {int /*<<< orphan*/ * output; } ;

/* Variables and functions */
 size_t COMP_VIDEO_ENCODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_1 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_11 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_12 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_13 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_1b ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_2 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_21 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_22 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_3 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_31 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_32 ; 
 int /*<<< orphan*/  MMAL_VIDEO_LEVEL_H264_4 ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_BASELINE ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_CONSTRAINED_BASELINE ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  MMAL_VIDEO_PROFILE_H264_MAIN ; 
 scalar_t__ V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 scalar_t__ V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1B 143 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_0 142 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_1 141 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_2 140 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_1_3 139 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_0 138 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_1 137 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_2_2 136 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_0 135 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_1 134 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_3_2 133 
#define  V4L2_MPEG_VIDEO_H264_LEVEL_4_0 132 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 131 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE 130 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH 129 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN 128 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mmal_parameter_video_profile*,int) ; 

__attribute__((used)) static int ctrl_set_video_encode_profile_level(struct bm2835_mmal_dev *dev,
					       struct v4l2_ctrl *ctrl,
					       const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	struct mmal_parameter_video_profile param;
	int ret = 0;

	if (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_PROFILE) {
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
		case V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE:
		case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
		case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
			dev->capture.enc_profile = ctrl->val;
			break;
		default:
			ret = -EINVAL;
			break;
		}
	} else if (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_LEVEL) {
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		case V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		case V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
			dev->capture.enc_level = ctrl->val;
			break;
		default:
			ret = -EINVAL;
			break;
		}
	}

	if (!ret) {
		switch (dev->capture.enc_profile) {
		case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
			param.profile = MMAL_VIDEO_PROFILE_H264_BASELINE;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE:
			param.profile =
				MMAL_VIDEO_PROFILE_H264_CONSTRAINED_BASELINE;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
			param.profile = MMAL_VIDEO_PROFILE_H264_MAIN;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
			param.profile = MMAL_VIDEO_PROFILE_H264_HIGH;
			break;
		default:
			/* Should never get here */
			break;
		}

		switch (dev->capture.enc_level) {
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
			param.level = MMAL_VIDEO_LEVEL_H264_1;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1B:
			param.level = MMAL_VIDEO_LEVEL_H264_1b;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
			param.level = MMAL_VIDEO_LEVEL_H264_11;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
			param.level = MMAL_VIDEO_LEVEL_H264_12;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
			param.level = MMAL_VIDEO_LEVEL_H264_13;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
			param.level = MMAL_VIDEO_LEVEL_H264_2;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
			param.level = MMAL_VIDEO_LEVEL_H264_21;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
			param.level = MMAL_VIDEO_LEVEL_H264_22;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
			param.level = MMAL_VIDEO_LEVEL_H264_3;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
			param.level = MMAL_VIDEO_LEVEL_H264_31;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
			param.level = MMAL_VIDEO_LEVEL_H264_32;
			break;
		case V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
			param.level = MMAL_VIDEO_LEVEL_H264_4;
			break;
		default:
			/* Should never get here */
			break;
		}

		ret = vchiq_mmal_port_parameter_set(dev->instance,
						    &dev->component[COMP_VIDEO_ENCODE]->output[0],
			mmal_ctrl->mmal_id,
			&param, sizeof(param));
	}
	return ret;
}