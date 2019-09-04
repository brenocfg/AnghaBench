#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int error; } ;
struct TYPE_7__ {void* global_alpha; void* vflip; void* hflip; void* rotate; } ;
struct mtk_mdp_ctx {int ctrls_rdy; TYPE_3__* mdp_dev; TYPE_4__ ctrl_handler; TYPE_1__ ctrls; } ;
struct TYPE_9__ {TYPE_2__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_MDP_MAX_CTRL_NUM ; 
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_ROTATE ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtk_mdp_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_ctrls_create(struct mtk_mdp_ctx *ctx)
{
	v4l2_ctrl_handler_init(&ctx->ctrl_handler, MTK_MDP_MAX_CTRL_NUM);

	ctx->ctrls.rotate = v4l2_ctrl_new_std(&ctx->ctrl_handler,
			&mtk_mdp_ctrl_ops, V4L2_CID_ROTATE, 0, 270, 90, 0);
	ctx->ctrls.hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					     &mtk_mdp_ctrl_ops,
					     V4L2_CID_HFLIP,
					     0, 1, 1, 0);
	ctx->ctrls.vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					     &mtk_mdp_ctrl_ops,
					     V4L2_CID_VFLIP,
					     0, 1, 1, 0);
	ctx->ctrls.global_alpha = v4l2_ctrl_new_std(&ctx->ctrl_handler,
						    &mtk_mdp_ctrl_ops,
						    V4L2_CID_ALPHA_COMPONENT,
						    0, 255, 1, 0);
	ctx->ctrls_rdy = ctx->ctrl_handler.error == 0;

	if (ctx->ctrl_handler.error) {
		int err = ctx->ctrl_handler.error;

		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		dev_err(&ctx->mdp_dev->pdev->dev,
			"Failed to create control handlers\n");
		return err;
	}

	return 0;
}