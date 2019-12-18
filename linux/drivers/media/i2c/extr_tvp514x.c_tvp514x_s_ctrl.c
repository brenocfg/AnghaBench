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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int val; int /*<<< orphan*/  id; } ;
struct tvp514x_decoder {TYPE_1__* tvp514x_regs; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t REG_AFE_GAIN_CTRL ; 
 size_t REG_BRIGHTNESS ; 
 size_t REG_CONTRAST ; 
 size_t REG_HUE ; 
 size_t REG_SATURATION ; 
#define  V4L2_CID_AUTOGAIN 132 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  debug ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int tvp514x_write_reg (struct v4l2_subdev*,size_t,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tvp514x_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct tvp514x_decoder *decoder = to_decoder(sd);
	int err = -EINVAL, value;

	value = ctrl->val;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		err = tvp514x_write_reg(sd, REG_BRIGHTNESS, value);
		if (!err)
			decoder->tvp514x_regs[REG_BRIGHTNESS].val = value;
		break;
	case V4L2_CID_CONTRAST:
		err = tvp514x_write_reg(sd, REG_CONTRAST, value);
		if (!err)
			decoder->tvp514x_regs[REG_CONTRAST].val = value;
		break;
	case V4L2_CID_SATURATION:
		err = tvp514x_write_reg(sd, REG_SATURATION, value);
		if (!err)
			decoder->tvp514x_regs[REG_SATURATION].val = value;
		break;
	case V4L2_CID_HUE:
		if (value == 180)
			value = 0x7F;
		else if (value == -180)
			value = 0x80;
		err = tvp514x_write_reg(sd, REG_HUE, value);
		if (!err)
			decoder->tvp514x_regs[REG_HUE].val = value;
		break;
	case V4L2_CID_AUTOGAIN:
		err = tvp514x_write_reg(sd, REG_AFE_GAIN_CTRL, value ? 0x0f : 0x0c);
		if (!err)
			decoder->tvp514x_regs[REG_AFE_GAIN_CTRL].val = value;
		break;
	}

	v4l2_dbg(1, debug, sd, "Set Control: ID - %d - %d\n",
			ctrl->id, ctrl->val);
	return err;
}