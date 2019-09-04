#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int flags; int id; int /*<<< orphan*/  val; } ;
struct gsc_variant {int dummy; } ;
struct gsc_dev {struct gsc_variant* variant; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int /*<<< orphan*/  alpha; TYPE_3__ crop; } ;
struct TYPE_11__ {TYPE_4__* rotate; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_1__ crop; } ;
struct gsc_ctx {unsigned int state; TYPE_6__ d_frame; int /*<<< orphan*/  rotation; int /*<<< orphan*/  out_path; TYPE_5__ gsc_ctrls; TYPE_2__ s_frame; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; struct gsc_dev* gsc_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GSC_DST_FMT ; 
 unsigned int GSC_PARAMS ; 
 unsigned int GSC_SRC_FMT ; 
#define  V4L2_CID_ALPHA_COMPONENT 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_ROTATE 129 
#define  V4L2_CID_VFLIP 128 
 int V4L2_CTRL_FLAG_INACTIVE ; 
 int gsc_check_scaler_ratio (struct gsc_variant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __gsc_s_ctrl(struct gsc_ctx *ctx, struct v4l2_ctrl *ctrl)
{
	struct gsc_dev *gsc = ctx->gsc_dev;
	struct gsc_variant *variant = gsc->variant;
	unsigned int flags = GSC_DST_FMT | GSC_SRC_FMT;
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
		if ((ctx->state & flags) == flags) {
			ret = gsc_check_scaler_ratio(variant,
					ctx->s_frame.crop.width,
					ctx->s_frame.crop.height,
					ctx->d_frame.crop.width,
					ctx->d_frame.crop.height,
					ctx->gsc_ctrls.rotate->val,
					ctx->out_path);

			if (ret)
				return -EINVAL;
		}

		ctx->rotation = ctrl->val;
		break;

	case V4L2_CID_ALPHA_COMPONENT:
		ctx->d_frame.alpha = ctrl->val;
		break;
	}

	ctx->state |= GSC_PARAMS;
	return 0;
}