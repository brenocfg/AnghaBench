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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; int /*<<< orphan*/  name; } ;
struct fimc_isp {int /*<<< orphan*/  subdev; } ;
struct fimc_is {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_CONTRAST ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_EXPOSURE ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_HUE ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_SATURATION ; 
 int /*<<< orphan*/  ISP_ADJUST_COMMAND_MANUAL_SHARPNESS ; 
 int /*<<< orphan*/  IS_ST_STREAM_ON ; 
#define  V4L2_CID_3A_LOCK 139 
#define  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE 138 
#define  V4L2_CID_BRIGHTNESS 137 
#define  V4L2_CID_COLORFX 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_EXPOSURE_ABSOLUTE 134 
#define  V4L2_CID_EXPOSURE_METERING 133 
#define  V4L2_CID_HUE 132 
#define  V4L2_CID_ISO_SENSITIVITY_AUTO 131 
#define  V4L2_CID_POWER_LINE_FREQUENCY 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int __ctrl_set_aewb_lock (struct fimc_is*,struct v4l2_ctrl*) ; 
 int __ctrl_set_afc (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctrl_set_image_effect (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int __ctrl_set_iso (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int __ctrl_set_metering (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int __ctrl_set_white_balance (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __is_set_isp_adjust (struct fimc_is*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fimc_isp* ctrl_to_fimc_isp (struct v4l2_ctrl*) ; 
 int fimc_is_itf_s_param (struct fimc_is*,int) ; 
 struct fimc_is* fimc_isp_to_is (struct fimc_isp*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_is_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct fimc_isp *isp = ctrl_to_fimc_isp(ctrl);
	struct fimc_is *is = fimc_isp_to_is(isp);
	bool set_param = true;
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_CONTRAST:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_CONTRAST,
				    ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_SATURATION,
				    ctrl->val);
		break;

	case V4L2_CID_SHARPNESS:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_SHARPNESS,
				    ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_ABSOLUTE:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_EXPOSURE,
				    ctrl->val);
		break;

	case V4L2_CID_BRIGHTNESS:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS,
				    ctrl->val);
		break;

	case V4L2_CID_HUE:
		__is_set_isp_adjust(is, ISP_ADJUST_COMMAND_MANUAL_HUE,
				    ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_METERING:
		ret = __ctrl_set_metering(is, ctrl->val);
		break;

	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		ret = __ctrl_set_white_balance(is, ctrl->val);
		break;

	case V4L2_CID_3A_LOCK:
		ret = __ctrl_set_aewb_lock(is, ctrl);
		set_param = false;
		break;

	case V4L2_CID_ISO_SENSITIVITY_AUTO:
		ret = __ctrl_set_iso(is, ctrl->val);
		break;

	case V4L2_CID_POWER_LINE_FREQUENCY:
		ret = __ctrl_set_afc(is, ctrl->val);
		break;

	case V4L2_CID_COLORFX:
		__ctrl_set_image_effect(is, ctrl->val);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0) {
		v4l2_err(&isp->subdev, "Failed to set control: %s (%d)\n",
						ctrl->name, ctrl->val);
		return ret;
	}

	if (set_param && test_bit(IS_ST_STREAM_ON, &is->state))
		return fimc_is_itf_s_param(is, true);

	return 0;
}