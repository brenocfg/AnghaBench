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
struct v4l2_ctrl_handler {int dummy; } ;
struct isc_ctrls {int /*<<< orphan*/  hist_stat; struct v4l2_ctrl_handler handler; } ;
struct isc_device {struct isc_ctrls ctrls; } ;

/* Variables and functions */
 int GAMMA_MAX ; 
 int /*<<< orphan*/  HIST_INIT ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_GAMMA ; 
 struct v4l2_ctrl_ops isc_ctrl_ops ; 
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

	ret = v4l2_ctrl_handler_init(hdl, 4);
	if (ret < 0)
		return ret;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -1024, 1023, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -2048, 2047, 1, 256);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAMMA, 0, GAMMA_MAX, 1, 2);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);

	v4l2_ctrl_handler_setup(hdl);

	return 0;
}