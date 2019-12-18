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
struct v4l2_ctrl_ops {int dummy; } ;
struct v4l2_ctrl_handler {int error; } ;
struct isc_ctrls {int contrast; scalar_t__ brightness; int /*<<< orphan*/  hist_stat; struct v4l2_ctrl_handler handler; } ;
struct isc_device {int /*<<< orphan*/  do_wb_ctrl; struct isc_ctrls ctrls; } ;

/* Variables and functions */
 int GAMMA_MAX ; 
 int /*<<< orphan*/  HIST_INIT ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_DO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_GAMMA ; 
 struct v4l2_ctrl_ops isc_ctrl_ops ; 
 int /*<<< orphan*/  isc_reset_awb_ctrls (struct isc_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_activate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int isc_ctrl_init(struct isc_device *isc)
{
	const struct v4l2_ctrl_ops *ops = &isc_ctrl_ops;
	struct isc_ctrls *ctrls = &isc->ctrls;
	struct v4l2_ctrl_handler *hdl = &ctrls->handler;
	int ret;

	ctrls->hist_stat = HIST_INIT;
	isc_reset_awb_ctrls(isc);

	ret = v4l2_ctrl_handler_init(hdl, 5);
	if (ret < 0)
		return ret;

	ctrls->brightness = 0;
	ctrls->contrast = 256;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -1024, 1023, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -2048, 2047, 1, 256);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAMMA, 0, GAMMA_MAX, 1, 2);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);

	/* do_white_balance is a button, so min,max,step,default are ignored */
	isc->do_wb_ctrl = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_DO_WHITE_BALANCE,
					    0, 0, 0, 0);

	if (!isc->do_wb_ctrl) {
		ret = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		return ret;
	}

	v4l2_ctrl_activate(isc->do_wb_ctrl, false);

	v4l2_ctrl_handler_setup(hdl);

	return 0;
}