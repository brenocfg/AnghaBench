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
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_handler {int error; } ;
struct s5k5baf_ctrls {void* auto_exp; void* gain; void* exposure; void* hflip; void* vflip; void* awb; void* gain_blue; void* gain_red; struct v4l2_ctrl_handler handler; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct s5k5baf {TYPE_1__ sd; struct s5k5baf_ctrls ctrls; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int S5K5BAF_GAIN_BLUE_DEF ; 
 int S5K5BAF_GAIN_RED_DEF ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BLUE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY ; 
 int /*<<< orphan*/  V4L2_CID_POWER_LINE_FREQUENCY_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_RED_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_SHARPNESS ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_CID_WHITE_BALANCE_TEMPERATURE ; 
 int /*<<< orphan*/  V4L2_COLORFX_NONE ; 
 int /*<<< orphan*/  V4L2_COLORFX_SKY_BLUE ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 struct v4l2_ctrl_ops s5k5baf_ctrl_ops ; 
 int /*<<< orphan*/  s5k5baf_test_pattern_menu ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*,int) ; 

__attribute__((used)) static int s5k5baf_initialize_ctrls(struct s5k5baf *state)
{
	const struct v4l2_ctrl_ops *ops = &s5k5baf_ctrl_ops;
	struct s5k5baf_ctrls *ctrls = &state->ctrls;
	struct v4l2_ctrl_handler *hdl = &ctrls->handler;
	int ret;

	ret = v4l2_ctrl_handler_init(hdl, 16);
	if (ret < 0) {
		v4l2_err(&state->sd, "cannot init ctrl handler (%d)\n", ret);
		return ret;
	}

	/* Auto white balance cluster */
	ctrls->awb = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTO_WHITE_BALANCE,
				       0, 1, 1, 1);
	ctrls->gain_red = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_RED_BALANCE,
					    0, 255, 1, S5K5BAF_GAIN_RED_DEF);
	ctrls->gain_blue = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BLUE_BALANCE,
					     0, 255, 1, S5K5BAF_GAIN_BLUE_DEF);
	v4l2_ctrl_auto_cluster(3, &ctrls->awb, 0, false);

	ctrls->hflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctrls->vflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_cluster(2, &ctrls->hflip);

	ctrls->auto_exp = v4l2_ctrl_new_std_menu(hdl, ops,
				V4L2_CID_EXPOSURE_AUTO,
				V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	/* Exposure time: x 1 us */
	ctrls->exposure = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_EXPOSURE,
					    0, 6000000U, 1, 100000U);
	/* Total gain: 256 <=> 1x */
	ctrls->gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAIN,
					0, 256, 1, 256);
	v4l2_ctrl_auto_cluster(3, &ctrls->auto_exp, 0, false);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_POWER_LINE_FREQUENCY,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_COLORFX,
			       V4L2_COLORFX_SKY_BLUE, ~0x6f, V4L2_COLORFX_NONE);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_WHITE_BALANCE_TEMPERATURE,
			  0, 256, 1, 0);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS, -127, 127, 1, 0);

	v4l2_ctrl_new_std_menu_items(hdl, ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(s5k5baf_test_pattern_menu) - 1,
				     0, 0, s5k5baf_test_pattern_menu);

	if (hdl->error) {
		v4l2_err(&state->sd, "error creating controls (%d)\n",
			 hdl->error);
		ret = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		return ret;
	}

	state->sd.ctrl_handler = hdl;
	return 0;
}