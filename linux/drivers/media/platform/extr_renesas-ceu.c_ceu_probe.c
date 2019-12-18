#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {scalar_t__ platform_data; scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/ * v4l2_dev; } ;
struct ceu_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__ notifier; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  base; int /*<<< orphan*/  mlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  capture; struct device* dev; } ;
struct ceu_data {int /*<<< orphan*/  irq_mask; } ;
struct TYPE_6__ {struct ceu_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct ceu_data ceu_data_sh4 ; 
 int /*<<< orphan*/  ceu_irq ; 
 int /*<<< orphan*/  ceu_notify_ops ; 
 int /*<<< orphan*/  ceu_of_match ; 
 int ceu_parse_dt (struct ceu_device*) ; 
 int ceu_parse_platform_data (struct ceu_device*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ceu_device*) ; 
 int /*<<< orphan*/  kfree (struct ceu_device*) ; 
 struct ceu_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ceu_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_1__*) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int v4l2_device_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct ceu_data *ceu_data;
	struct ceu_device *ceudev;
	struct resource *res;
	unsigned int irq;
	int num_subdevs;
	int ret;

	ceudev = kzalloc(sizeof(*ceudev), GFP_KERNEL);
	if (!ceudev)
		return -ENOMEM;

	platform_set_drvdata(pdev, ceudev);
	ceudev->dev = dev;

	INIT_LIST_HEAD(&ceudev->capture);
	spin_lock_init(&ceudev->lock);
	mutex_init(&ceudev->mlock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ceudev->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ceudev->base)) {
		ret = PTR_ERR(ceudev->base);
		goto error_free_ceudev;
	}

	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto error_free_ceudev;
	irq = ret;

	ret = devm_request_irq(dev, irq, ceu_irq,
			       0, dev_name(dev), ceudev);
	if (ret) {
		dev_err(&pdev->dev, "Unable to request CEU interrupt.\n");
		goto error_free_ceudev;
	}

	pm_runtime_enable(dev);

	ret = v4l2_device_register(dev, &ceudev->v4l2_dev);
	if (ret)
		goto error_pm_disable;

	v4l2_async_notifier_init(&ceudev->notifier);

	if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
		ceu_data = of_match_device(ceu_of_match, dev)->data;
		num_subdevs = ceu_parse_dt(ceudev);
	} else if (dev->platform_data) {
		/* Assume SH4 if booting with platform data. */
		ceu_data = &ceu_data_sh4;
		num_subdevs = ceu_parse_platform_data(ceudev,
						      dev->platform_data);
	} else {
		num_subdevs = -EINVAL;
	}

	if (num_subdevs < 0) {
		ret = num_subdevs;
		goto error_v4l2_unregister;
	}
	ceudev->irq_mask = ceu_data->irq_mask;

	ceudev->notifier.v4l2_dev	= &ceudev->v4l2_dev;
	ceudev->notifier.ops		= &ceu_notify_ops;
	ret = v4l2_async_notifier_register(&ceudev->v4l2_dev,
					   &ceudev->notifier);
	if (ret)
		goto error_cleanup;

	dev_info(dev, "Renesas Capture Engine Unit %s\n", dev_name(dev));

	return 0;

error_cleanup:
	v4l2_async_notifier_cleanup(&ceudev->notifier);
error_v4l2_unregister:
	v4l2_device_unregister(&ceudev->v4l2_dev);
error_pm_disable:
	pm_runtime_disable(dev);
error_free_ceudev:
	kfree(ceudev);

	return ret;
}