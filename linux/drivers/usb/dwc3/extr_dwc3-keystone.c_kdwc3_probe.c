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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dwc3_keystone {struct device* dev; int /*<<< orphan*/  usbss; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct dwc3_keystone* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwc3_keystone*) ; 
 int /*<<< orphan*/  dwc3_keystone_interrupt ; 
 int /*<<< orphan*/  kdwc3_disable_irqs (struct dwc3_keystone*) ; 
 int /*<<< orphan*/  kdwc3_enable_irqs (struct dwc3_keystone*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dwc3_keystone*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static int kdwc3_probe(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct device_node	*node = pdev->dev.of_node;
	struct dwc3_keystone	*kdwc;
	int			error, irq;

	kdwc = devm_kzalloc(dev, sizeof(*kdwc), GFP_KERNEL);
	if (!kdwc)
		return -ENOMEM;

	platform_set_drvdata(pdev, kdwc);

	kdwc->dev = dev;

	kdwc->usbss = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(kdwc->usbss))
		return PTR_ERR(kdwc->usbss);

	pm_runtime_enable(kdwc->dev);

	error = pm_runtime_get_sync(kdwc->dev);
	if (error < 0) {
		dev_err(kdwc->dev, "pm_runtime_get_sync failed, error %d\n",
			error);
		goto err_irq;
	}

	/* IRQ processing not required currently for AM65 */
	if (of_device_is_compatible(node, "ti,am654-dwc3"))
		goto skip_irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		error = irq;
		goto err_irq;
	}

	error = devm_request_irq(dev, irq, dwc3_keystone_interrupt, IRQF_SHARED,
			dev_name(dev), kdwc);
	if (error) {
		dev_err(dev, "failed to request IRQ #%d --> %d\n",
				irq, error);
		goto err_irq;
	}

	kdwc3_enable_irqs(kdwc);

skip_irq:
	error = of_platform_populate(node, NULL, NULL, dev);
	if (error) {
		dev_err(&pdev->dev, "failed to create dwc3 core\n");
		goto err_core;
	}

	return 0;

err_core:
	kdwc3_disable_irqs(kdwc);
err_irq:
	pm_runtime_put_sync(kdwc->dev);
	pm_runtime_disable(kdwc->dev);

	return error;
}