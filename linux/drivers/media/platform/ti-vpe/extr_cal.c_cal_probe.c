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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct cal_dev {struct cal_ctx** ctx; void** cc; void* cm; TYPE_2__* res; void* base; struct platform_device* pdev; TYPE_1__ v4l2_dev; } ;
struct cal_ctx {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  notifier; } ;
struct TYPE_5__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_MODULE_NAME ; 
 int CAL_NUM_CONTEXT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* cal_create_instance (struct cal_dev*,int) ; 
 int /*<<< orphan*/  cal_dbg (int,struct cal_dev*,char*,int,...) ; 
 int /*<<< orphan*/  cal_err (struct cal_dev*,char*) ; 
 int /*<<< orphan*/  cal_get_hwinfo (struct cal_dev*) ; 
 int /*<<< orphan*/  cal_irq ; 
 int cal_runtime_get (struct cal_dev*) ; 
 int /*<<< orphan*/  cal_runtime_put (struct cal_dev*) ; 
 void* cc_create (struct cal_dev*,int) ; 
 void* cm_create (struct cal_dev*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct cal_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cal_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cal_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cal_probe(struct platform_device *pdev)
{
	struct cal_dev *dev;
	struct cal_ctx *ctx;
	int ret;
	int irq;
	int i;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	/* set pseudo v4l2 device name so we can use v4l2_printk */
	strscpy(dev->v4l2_dev.name, CAL_MODULE_NAME,
		sizeof(dev->v4l2_dev.name));

	/* save pdev pointer */
	dev->pdev = pdev;

	dev->res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						"cal_top");
	dev->base = devm_ioremap_resource(&pdev->dev, dev->res);
	if (IS_ERR(dev->base))
		return PTR_ERR(dev->base);

	cal_dbg(1, dev, "ioresource %s at %pa - %pa\n",
		dev->res->name, &dev->res->start, &dev->res->end);

	irq = platform_get_irq(pdev, 0);
	cal_dbg(1, dev, "got irq# %d\n", irq);
	ret = devm_request_irq(&pdev->dev, irq, cal_irq, 0, CAL_MODULE_NAME,
			       dev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, dev);

	dev->cm = cm_create(dev);
	if (IS_ERR(dev->cm))
		return PTR_ERR(dev->cm);

	dev->cc[0] = cc_create(dev, 0);
	if (IS_ERR(dev->cc[0]))
		return PTR_ERR(dev->cc[0]);

	dev->cc[1] = cc_create(dev, 1);
	if (IS_ERR(dev->cc[1]))
		return PTR_ERR(dev->cc[1]);

	dev->ctx[0] = NULL;
	dev->ctx[1] = NULL;

	dev->ctx[0] = cal_create_instance(dev, 0);
	dev->ctx[1] = cal_create_instance(dev, 1);
	if (!dev->ctx[0] && !dev->ctx[1]) {
		cal_err(dev, "Neither port is configured, no point in staying up\n");
		return -ENODEV;
	}

	pm_runtime_enable(&pdev->dev);

	ret = cal_runtime_get(dev);
	if (ret)
		goto runtime_disable;

	/* Just check we can actually access the module */
	cal_get_hwinfo(dev);

	cal_runtime_put(dev);

	return 0;

runtime_disable:
	pm_runtime_disable(&pdev->dev);
	for (i = 0; i < CAL_NUM_CONTEXT; i++) {
		ctx = dev->ctx[i];
		if (ctx) {
			v4l2_async_notifier_unregister(&ctx->notifier);
			v4l2_async_notifier_cleanup(&ctx->notifier);
			v4l2_ctrl_handler_free(&ctx->ctrl_handler);
			v4l2_device_unregister(&ctx->v4l2_dev);
		}
	}

	return ret;
}