#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int error; } ;
struct TYPE_5__ {void* vflip; void* hflip; } ;
struct bdisp_ctx {int ctrls_rdy; TYPE_2__ ctrl_handler; TYPE_1__ bdisp_ctrls; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDISP_MAX_CTRL_NUM ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  bdisp_c_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdisp_ctrls_create(struct bdisp_ctx *ctx)
{
	if (ctx->ctrls_rdy)
		return 0;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, BDISP_MAX_CTRL_NUM);

	ctx->bdisp_ctrls.hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&bdisp_c_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctx->bdisp_ctrls.vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
				&bdisp_c_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);

	if (ctx->ctrl_handler.error) {
		int err = ctx->ctrl_handler.error;

		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		return err;
	}

	ctx->ctrls_rdy = true;

	return 0;
}