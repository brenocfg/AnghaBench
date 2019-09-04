#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int dummy; } ;
struct cal_dev {int /*<<< orphan*/ * cc; TYPE_1__* pdev; } ;
struct TYPE_5__ {struct v4l2_ctrl_handler* ctrl_handler; int /*<<< orphan*/  name; } ;
struct cal_ctx {int csi2_port; TYPE_2__ v4l2_dev; int /*<<< orphan*/  cc; struct v4l2_ctrl_handler ctrl_handler; struct cal_dev* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char* CAL_MODULE_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ctx_err (struct cal_ctx*,char*) ; 
 struct cal_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int of_cal_create_instance (struct cal_ctx*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_2__*) ; 

__attribute__((used)) static struct cal_ctx *cal_create_instance(struct cal_dev *dev, int inst)
{
	struct cal_ctx *ctx;
	struct v4l2_ctrl_handler *hdl;
	int ret;

	ctx = devm_kzalloc(&dev->pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	/* save the cal_dev * for future ref */
	ctx->dev = dev;

	snprintf(ctx->v4l2_dev.name, sizeof(ctx->v4l2_dev.name),
		 "%s-%03d", CAL_MODULE_NAME, inst);
	ret = v4l2_device_register(&dev->pdev->dev, &ctx->v4l2_dev);
	if (ret)
		goto err_exit;

	hdl = &ctx->ctrl_handler;
	ret = v4l2_ctrl_handler_init(hdl, 11);
	if (ret) {
		ctx_err(ctx, "Failed to init ctrl handler\n");
		goto unreg_dev;
	}
	ctx->v4l2_dev.ctrl_handler = hdl;

	/* Make sure Camera Core H/W register area is available */
	ctx->cc = dev->cc[inst];

	/* Store the instance id */
	ctx->csi2_port = inst + 1;

	ret = of_cal_create_instance(ctx, inst);
	if (ret) {
		ret = -EINVAL;
		goto free_hdl;
	}
	return ctx;

free_hdl:
	v4l2_ctrl_handler_free(hdl);
unreg_dev:
	v4l2_device_unregister(&ctx->v4l2_dev);
err_exit:
	return NULL;
}