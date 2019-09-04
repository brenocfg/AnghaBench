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
struct v4l2_ctrl {int dummy; } ;
struct cal_ctx {int /*<<< orphan*/  external_rate; TYPE_1__* sensor; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPIPE ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_err (struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl_int64 (struct v4l2_ctrl*) ; 

__attribute__((used)) static int cal_get_external_info(struct cal_ctx *ctx)
{
	struct v4l2_ctrl *ctrl;

	if (!ctx->sensor)
		return -ENODEV;

	ctrl = v4l2_ctrl_find(ctx->sensor->ctrl_handler, V4L2_CID_PIXEL_RATE);
	if (!ctrl) {
		ctx_err(ctx, "no pixel rate control in subdev: %s\n",
			ctx->sensor->name);
		return -EPIPE;
	}

	ctx->external_rate = v4l2_ctrl_g_ctrl_int64(ctrl);
	ctx_dbg(3, ctx, "sensor Pixel Rate: %d\n", ctx->external_rate);

	return 0;
}