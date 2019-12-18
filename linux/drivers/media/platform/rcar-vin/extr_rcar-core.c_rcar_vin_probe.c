#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_device_attribute {TYPE_4__* data; } ;
struct rvin_dev {int alpha; TYPE_1__* group; int /*<<< orphan*/  v4l2_dev; TYPE_4__* info; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  base; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ use_mc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_2__ notifier; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct rvin_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rvin_dev*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r8a7795es1 ; 
 int rvin_dma_register (struct rvin_dev*,int) ; 
 int /*<<< orphan*/  rvin_dma_unregister (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_group_put (struct rvin_dev*) ; 
 int rvin_mc_init (struct rvin_dev*) ; 
 int rvin_parallel_init (struct rvin_dev*) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_vin_probe(struct platform_device *pdev)
{
	const struct soc_device_attribute *attr;
	struct rvin_dev *vin;
	struct resource *mem;
	int irq, ret;

	vin = devm_kzalloc(&pdev->dev, sizeof(*vin), GFP_KERNEL);
	if (!vin)
		return -ENOMEM;

	vin->dev = &pdev->dev;
	vin->info = of_device_get_match_data(&pdev->dev);
	vin->alpha = 0xff;

	/*
	 * Special care is needed on r8a7795 ES1.x since it
	 * uses different routing than r8a7795 ES2.0.
	 */
	attr = soc_device_match(r8a7795es1);
	if (attr)
		vin->info = attr->data;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (mem == NULL)
		return -EINVAL;

	vin->base = devm_ioremap_resource(vin->dev, mem);
	if (IS_ERR(vin->base))
		return PTR_ERR(vin->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = rvin_dma_register(vin, irq);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, vin);

	if (vin->info->use_mc) {
		ret = rvin_mc_init(vin);
		if (ret)
			goto error_dma_unregister;
	}

	ret = rvin_parallel_init(vin);
	if (ret)
		goto error_group_unregister;

	pm_suspend_ignore_children(&pdev->dev, true);
	pm_runtime_enable(&pdev->dev);

	return 0;

error_group_unregister:
	v4l2_ctrl_handler_free(&vin->ctrl_handler);

	if (vin->info->use_mc) {
		mutex_lock(&vin->group->lock);
		if (&vin->v4l2_dev == vin->group->notifier.v4l2_dev) {
			v4l2_async_notifier_unregister(&vin->group->notifier);
			v4l2_async_notifier_cleanup(&vin->group->notifier);
		}
		mutex_unlock(&vin->group->lock);
		rvin_group_put(vin);
	}

error_dma_unregister:
	rvin_dma_unregister(vin);

	return ret;
}