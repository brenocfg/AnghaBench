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
struct v4l2_ctrl {int id; int val; } ;
struct tw2804 {int /*<<< orphan*/  channel; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TW2804_REG_AUTOGAIN ; 
 int TW2804_REG_BLUE_BALANCE ; 
 int TW2804_REG_BRIGHTNESS ; 
 int TW2804_REG_CHROMA_GAIN ; 
 int TW2804_REG_COLOR_KILLER ; 
 int TW2804_REG_CONTRAST ; 
 int TW2804_REG_GAIN ; 
 int TW2804_REG_HUE ; 
 int TW2804_REG_RED_BALANCE ; 
 int TW2804_REG_SATURATION ; 
#define  V4L2_CID_AUTOGAIN 137 
#define  V4L2_CID_BLUE_BALANCE 136 
#define  V4L2_CID_BRIGHTNESS 135 
#define  V4L2_CID_CHROMA_GAIN 134 
#define  V4L2_CID_COLOR_KILLER 133 
#define  V4L2_CID_CONTRAST 132 
#define  V4L2_CID_GAIN 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_RED_BALANCE 129 
#define  V4L2_CID_SATURATION 128 
 int read_reg (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct tw2804* to_state_from_ctrl (struct v4l2_ctrl*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 
 int write_reg (struct i2c_client*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw2804_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct tw2804 *state = to_state_from_ctrl(ctrl);
	struct i2c_client *client = v4l2_get_subdevdata(&state->sd);
	int addr;
	int reg;

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		addr = TW2804_REG_AUTOGAIN;
		reg = read_reg(client, addr, state->channel);
		if (reg < 0)
			return reg;
		if (ctrl->val == 0)
			reg &= ~(1 << 7);
		else
			reg |= 1 << 7;
		return write_reg(client, addr, reg, state->channel);

	case V4L2_CID_COLOR_KILLER:
		addr = TW2804_REG_COLOR_KILLER;
		reg = read_reg(client, addr, state->channel);
		if (reg < 0)
			return reg;
		reg = (reg & ~(0x03)) | (ctrl->val == 0 ? 0x02 : 0x03);
		return write_reg(client, addr, reg, state->channel);

	case V4L2_CID_GAIN:
		return write_reg(client, TW2804_REG_GAIN, ctrl->val, 0);

	case V4L2_CID_CHROMA_GAIN:
		return write_reg(client, TW2804_REG_CHROMA_GAIN, ctrl->val, 0);

	case V4L2_CID_BLUE_BALANCE:
		return write_reg(client, TW2804_REG_BLUE_BALANCE, ctrl->val, 0);

	case V4L2_CID_RED_BALANCE:
		return write_reg(client, TW2804_REG_RED_BALANCE, ctrl->val, 0);

	case V4L2_CID_BRIGHTNESS:
		return write_reg(client, TW2804_REG_BRIGHTNESS,
				ctrl->val, state->channel);

	case V4L2_CID_CONTRAST:
		return write_reg(client, TW2804_REG_CONTRAST,
				ctrl->val, state->channel);

	case V4L2_CID_SATURATION:
		return write_reg(client, TW2804_REG_SATURATION,
				ctrl->val, state->channel);

	case V4L2_CID_HUE:
		return write_reg(client, TW2804_REG_HUE,
				ctrl->val, state->channel);

	default:
		break;
	}
	return -EINVAL;
}