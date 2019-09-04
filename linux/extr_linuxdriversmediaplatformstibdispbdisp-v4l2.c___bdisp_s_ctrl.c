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
struct v4l2_ctrl {int flags; int id; int /*<<< orphan*/  val; } ;
struct bdisp_ctx {int /*<<< orphan*/  state; TYPE_1__* bdisp_dev; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDISP_PARAMS ; 
 int EINVAL ; 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int V4L2_CTRL_FLAG_INACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int __bdisp_s_ctrl(struct bdisp_ctx *ctx, struct v4l2_ctrl *ctrl)
{
	if (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		break;
	case V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		break;
	default:
		dev_err(ctx->bdisp_dev->dev, "unknown control %d\n", ctrl->id);
		return -EINVAL;
	}

	ctx->state |= BDISP_PARAMS;

	return 0;
}