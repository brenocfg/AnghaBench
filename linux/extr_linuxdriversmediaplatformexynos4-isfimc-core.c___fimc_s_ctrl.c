#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int flags; int id; int val; } ;
struct fimc_variant {int /*<<< orphan*/  has_out_rot; } ;
struct fimc_dev {int /*<<< orphan*/  state; struct fimc_variant* variant; } ;
struct TYPE_4__ {int alpha; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct fimc_ctx {int hflip; int vflip; int rotation; int /*<<< orphan*/  state; TYPE_2__ d_frame; TYPE_1__ s_frame; struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIMC_PARAMS ; 
 int /*<<< orphan*/  ST_CAPT_APPLY_CFG ; 
#define  V4L2_CID_ALPHA_COMPONENT 132 
#define  V4L2_CID_COLORFX 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_ROTATE 129 
#define  V4L2_CID_VFLIP 128 
 int V4L2_CTRL_FLAG_INACTIVE ; 
 int /*<<< orphan*/  fimc_capture_pending (struct fimc_dev*) ; 
 int fimc_check_scaler_ratio (struct fimc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fimc_set_color_effect (struct fimc_ctx*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __fimc_s_ctrl(struct fimc_ctx *ctx, struct v4l2_ctrl *ctrl)
{
	struct fimc_dev *fimc = ctx->fimc_dev;
	const struct fimc_variant *variant = fimc->variant;
	int ret = 0;

	if (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_HFLIP:
		ctx->hflip = ctrl->val;
		break;

	case V4L2_CID_VFLIP:
		ctx->vflip = ctrl->val;
		break;

	case V4L2_CID_ROTATE:
		if (fimc_capture_pending(fimc)) {
			ret = fimc_check_scaler_ratio(ctx, ctx->s_frame.width,
					ctx->s_frame.height, ctx->d_frame.width,
					ctx->d_frame.height, ctrl->val);
			if (ret)
				return -EINVAL;
		}
		if ((ctrl->val == 90 || ctrl->val == 270) &&
		    !variant->has_out_rot)
			return -EINVAL;

		ctx->rotation = ctrl->val;
		break;

	case V4L2_CID_ALPHA_COMPONENT:
		ctx->d_frame.alpha = ctrl->val;
		break;

	case V4L2_CID_COLORFX:
		ret = fimc_set_color_effect(ctx, ctrl->val);
		if (ret)
			return ret;
		break;
	}

	ctx->state |= FIMC_PARAMS;
	set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
	return 0;
}