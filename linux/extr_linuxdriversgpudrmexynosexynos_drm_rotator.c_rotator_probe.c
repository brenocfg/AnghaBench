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
struct rot_variant {int /*<<< orphan*/  num_formats; int /*<<< orphan*/  formats; } ;
struct rot_context {int /*<<< orphan*/  clock; int /*<<< orphan*/  regs; struct device* dev; int /*<<< orphan*/  num_formats; int /*<<< orphan*/  formats; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROTATOR_AUTOSUSPEND_DELAY ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct rot_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rot_context*) ; 
 struct rot_variant* of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rot_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  rotator_component_ops ; 
 int /*<<< orphan*/  rotator_irq_handler ; 

__attribute__((used)) static int rotator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource	*regs_res;
	struct rot_context *rot;
	const struct rot_variant *variant;
	int irq;
	int ret;

	rot = devm_kzalloc(dev, sizeof(*rot), GFP_KERNEL);
	if (!rot)
		return -ENOMEM;

	variant = of_device_get_match_data(dev);
	rot->formats = variant->formats;
	rot->num_formats = variant->num_formats;
	rot->dev = dev;
	regs_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rot->regs = devm_ioremap_resource(dev, regs_res);
	if (IS_ERR(rot->regs))
		return PTR_ERR(rot->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to get irq\n");
		return irq;
	}

	ret = devm_request_irq(dev, irq, rotator_irq_handler, 0, dev_name(dev),
			       rot);
	if (ret < 0) {
		dev_err(dev, "failed to request irq\n");
		return ret;
	}

	rot->clock = devm_clk_get(dev, "rotator");
	if (IS_ERR(rot->clock)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(rot->clock);
	}

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, ROTATOR_AUTOSUSPEND_DELAY);
	pm_runtime_enable(dev);
	platform_set_drvdata(pdev, rot);

	ret = component_add(dev, &rotator_component_ops);
	if (ret)
		goto err_component;

	return 0;

err_component:
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);
	return ret;
}