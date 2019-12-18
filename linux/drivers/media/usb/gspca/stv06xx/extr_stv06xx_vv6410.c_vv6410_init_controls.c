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
struct v4l2_ctrl_handler {int error; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler ctrl_handler; } ;
struct sd {TYPE_1__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vv6410_ctrl_ops ; 

__attribute__((used)) static int vv6410_init_controls(struct sd *sd)
{
	struct v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	v4l2_ctrl_handler_init(hdl, 2);
	/* Disable the hardware VFLIP and HFLIP as we currently lack a
	   mechanism to adjust the image offset in such a way that
	   we don't need to renegotiate the announced format */
	/* v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops, */
	/*		V4L2_CID_HFLIP, 0, 1, 1, 0); */
	/* v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops, */
	/*		V4L2_CID_VFLIP, 0, 1, 1, 0); */
	v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 32768, 1, 20000);
	v4l2_ctrl_new_std(hdl, &vv6410_ctrl_ops,
			V4L2_CID_GAIN, 0, 15, 1, 10);
	return hdl->error;
}