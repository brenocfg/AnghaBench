#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ val; } ;
struct v4l2_ctrl {scalar_t__ maximum; TYPE_2__ cur; } ;
struct fimc_dev {TYPE_4__* drv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmt; } ;
struct TYPE_7__ {struct v4l2_ctrl* alpha; } ;
struct fimc_ctx {TYPE_1__ d_frame; TYPE_3__ ctrls; struct fimc_dev* fimc_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  alpha_color; } ;

/* Variables and functions */
 scalar_t__ fimc_get_alpha_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_lock (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_unlock (struct v4l2_ctrl*) ; 

void fimc_alpha_ctrl_update(struct fimc_ctx *ctx)
{
	struct fimc_dev *fimc = ctx->fimc_dev;
	struct v4l2_ctrl *ctrl = ctx->ctrls.alpha;

	if (ctrl == NULL || !fimc->drv_data->alpha_color)
		return;

	v4l2_ctrl_lock(ctrl);
	ctrl->maximum = fimc_get_alpha_mask(ctx->d_frame.fmt);

	if (ctrl->cur.val > ctrl->maximum)
		ctrl->cur.val = ctrl->maximum;

	v4l2_ctrl_unlock(ctrl);
}