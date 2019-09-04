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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct elm_info {int /*<<< orphan*/  list; int /*<<< orphan*/  elm_completion; int /*<<< orphan*/  elm_base; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct elm_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct elm_info*) ; 
 int /*<<< orphan*/  elm_devices ; 
 int /*<<< orphan*/  elm_isr ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct elm_info*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elm_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct resource *res, *irq;
	struct elm_info *info;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "no irq resource defined\n");
		return -ENODEV;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->elm_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(info->elm_base))
		return PTR_ERR(info->elm_base);

	ret = devm_request_irq(&pdev->dev, irq->start, elm_isr, 0,
			pdev->name, info);
	if (ret) {
		dev_err(&pdev->dev, "failure requesting %pr\n", irq);
		return ret;
	}

	pm_runtime_enable(&pdev->dev);
	if (pm_runtime_get_sync(&pdev->dev) < 0) {
		ret = -EINVAL;
		pm_runtime_disable(&pdev->dev);
		dev_err(&pdev->dev, "can't enable clock\n");
		return ret;
	}

	init_completion(&info->elm_completion);
	INIT_LIST_HEAD(&info->list);
	list_add(&info->list, &elm_devices);
	platform_set_drvdata(pdev, info);
	return ret;
}