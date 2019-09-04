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
struct v4l2_ctrl {int /*<<< orphan*/  val; int /*<<< orphan*/  id; int /*<<< orphan*/  handler; } ;
struct max2175 {int dummy; } ;

/* Variables and functions */
#define  V4L2_CID_MAX2175_HSLS 130 
#define  V4L2_CID_MAX2175_I2S_ENABLE 129 
#define  V4L2_CID_MAX2175_RX_MODE 128 
 struct max2175* max2175_from_ctrl_hdl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_i2s_enable (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_s_ctrl_rx_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max2175_set_hsls (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct max2175 *ctx = max2175_from_ctrl_hdl(ctrl->handler);

	mxm_dbg(ctx, "s_ctrl: id 0x%x, val %u\n", ctrl->id, ctrl->val);
	switch (ctrl->id) {
	case V4L2_CID_MAX2175_I2S_ENABLE:
		max2175_i2s_enable(ctx, ctrl->val);
		break;
	case V4L2_CID_MAX2175_HSLS:
		max2175_set_hsls(ctx, ctrl->val);
		break;
	case V4L2_CID_MAX2175_RX_MODE:
		max2175_s_ctrl_rx_mode(ctx, ctrl->val);
		break;
	}

	return 0;
}