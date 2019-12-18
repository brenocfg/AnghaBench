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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cal_dev {struct cal_ctx** ctx; } ;
struct cal_ctx {int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_MODULE_NAME ; 
 int CAL_NUM_CONTEXT ; 
 int /*<<< orphan*/  cal_dbg (int,struct cal_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cal_runtime_get (struct cal_dev*) ; 
 int /*<<< orphan*/  cal_runtime_put (struct cal_dev*) ; 
 int /*<<< orphan*/  camerarx_phy_disable (struct cal_ctx*) ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cal_remove(struct platform_device *pdev)
{
	struct cal_dev *dev =
		(struct cal_dev *)platform_get_drvdata(pdev);
	struct cal_ctx *ctx;
	int i;

	cal_dbg(1, dev, "Removing %s\n", CAL_MODULE_NAME);

	cal_runtime_get(dev);

	for (i = 0; i < CAL_NUM_CONTEXT; i++) {
		ctx = dev->ctx[i];
		if (ctx) {
			ctx_dbg(1, ctx, "unregistering %s\n",
				video_device_node_name(&ctx->vdev));
			camerarx_phy_disable(ctx);
			v4l2_async_notifier_unregister(&ctx->notifier);
			v4l2_async_notifier_cleanup(&ctx->notifier);
			v4l2_ctrl_handler_free(&ctx->ctrl_handler);
			v4l2_device_unregister(&ctx->v4l2_dev);
			video_unregister_device(&ctx->vdev);
		}
	}

	cal_runtime_put(dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}