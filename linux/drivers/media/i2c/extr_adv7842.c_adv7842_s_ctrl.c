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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int val; } ;
struct adv7842_state {int rgb_quantization_range; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE 135 
#define  V4L2_CID_ADV_RX_FREE_RUN_COLOR 134 
#define  V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL 133 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_DV_RX_RGB_RANGE 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  afe_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  cp_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  cp_write_and_or (struct v4l2_subdev*,int,int,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  sdp_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  sdp_write_and_or (struct v4l2_subdev*,int,int,int) ; 
 int /*<<< orphan*/  set_rgb_quantization_range (struct v4l2_subdev*) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int,int) ; 

__attribute__((used)) static int adv7842_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct adv7842_state *state = to_state(sd);

	/* TODO SDP ctrls
	   contrast/brightness/hue/free run is acting a bit strange,
	   not sure if sdp csc is correct.
	 */
	switch (ctrl->id) {
	/* standard ctrls */
	case V4L2_CID_BRIGHTNESS:
		cp_write(sd, 0x3c, ctrl->val);
		sdp_write(sd, 0x14, ctrl->val);
		/* ignore lsb sdp 0x17[3:2] */
		return 0;
	case V4L2_CID_CONTRAST:
		cp_write(sd, 0x3a, ctrl->val);
		sdp_write(sd, 0x13, ctrl->val);
		/* ignore lsb sdp 0x17[1:0] */
		return 0;
	case V4L2_CID_SATURATION:
		cp_write(sd, 0x3b, ctrl->val);
		sdp_write(sd, 0x15, ctrl->val);
		/* ignore lsb sdp 0x17[5:4] */
		return 0;
	case V4L2_CID_HUE:
		cp_write(sd, 0x3d, ctrl->val);
		sdp_write(sd, 0x16, ctrl->val);
		/* ignore lsb sdp 0x17[7:6] */
		return 0;
		/* custom ctrls */
	case V4L2_CID_ADV_RX_ANALOG_SAMPLING_PHASE:
		afe_write(sd, 0xc8, ctrl->val);
		return 0;
	case V4L2_CID_ADV_RX_FREE_RUN_COLOR_MANUAL:
		cp_write_and_or(sd, 0xbf, ~0x04, (ctrl->val << 2));
		sdp_write_and_or(sd, 0xdd, ~0x04, (ctrl->val << 2));
		return 0;
	case V4L2_CID_ADV_RX_FREE_RUN_COLOR: {
		u8 R = (ctrl->val & 0xff0000) >> 16;
		u8 G = (ctrl->val & 0x00ff00) >> 8;
		u8 B = (ctrl->val & 0x0000ff);
		/* RGB -> YUV, numerical approximation */
		int Y = 66 * R + 129 * G + 25 * B;
		int U = -38 * R - 74 * G + 112 * B;
		int V = 112 * R - 94 * G - 18 * B;

		/* Scale down to 8 bits with rounding */
		Y = (Y + 128) >> 8;
		U = (U + 128) >> 8;
		V = (V + 128) >> 8;
		/* make U,V positive */
		Y += 16;
		U += 128;
		V += 128;

		v4l2_dbg(1, debug, sd, "R %x, G %x, B %x\n", R, G, B);
		v4l2_dbg(1, debug, sd, "Y %x, U %x, V %x\n", Y, U, V);

		/* CP */
		cp_write(sd, 0xc1, R);
		cp_write(sd, 0xc0, G);
		cp_write(sd, 0xc2, B);
		/* SDP */
		sdp_write(sd, 0xde, Y);
		sdp_write(sd, 0xdf, (V & 0xf0) | ((U >> 4) & 0x0f));
		return 0;
	}
	case V4L2_CID_DV_RX_RGB_RANGE:
		state->rgb_quantization_range = ctrl->val;
		set_rgb_quantization_range(sd);
		return 0;
	}
	return -EINVAL;
}