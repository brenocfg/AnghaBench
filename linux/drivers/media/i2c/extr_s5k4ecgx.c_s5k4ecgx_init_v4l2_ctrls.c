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
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct s5k4ecgx {TYPE_1__ sd; struct v4l2_ctrl_handler handler; } ;

/* Variables and functions */
 int SHARPNESS_DIV ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_SHARPNESS ; 
 struct v4l2_ctrl_ops s5k4ecgx_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,struct v4l2_ctrl_ops const*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int s5k4ecgx_init_v4l2_ctrls(struct s5k4ecgx *priv)
{
	const struct v4l2_ctrl_ops *ops = &s5k4ecgx_ctrl_ops;
	struct v4l2_ctrl_handler *hdl = &priv->handler;
	int ret;

	ret = v4l2_ctrl_handler_init(hdl, 4);
	if (ret)
		return ret;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -208, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION, -127, 127, 1, 0);

	/* Sharpness default is 24612, and then (24612/SHARPNESS_DIV) = 2 */
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS, -32704/SHARPNESS_DIV,
			  24612/SHARPNESS_DIV, 1, 2);
	if (hdl->error) {
		ret = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		return ret;
	}
	priv->sd.ctrl_handler = hdl;

	return 0;
}