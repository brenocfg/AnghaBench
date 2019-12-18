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
struct v4l2_ctrl_handler {int error; } ;
struct ipu_csc_scaler_ctx {struct v4l2_ctrl_handler ctrl_hdlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_ROTATE ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  ipu_csc_scaler_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_csc_scaler_init_controls(struct ipu_csc_scaler_ctx *ctx)
{
	struct v4l2_ctrl_handler *hdlr = &ctx->ctrl_hdlr;

	v4l2_ctrl_handler_init(hdlr, 3);

	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_HFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_VFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &ipu_csc_scaler_ctrl_ops, V4L2_CID_ROTATE,
			  0, 270, 90, 0);

	if (hdlr->error) {
		v4l2_ctrl_handler_free(hdlr);
		return hdlr->error;
	}

	v4l2_ctrl_handler_setup(hdlr);
	return 0;
}