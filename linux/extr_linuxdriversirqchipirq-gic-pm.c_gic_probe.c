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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct gic_clk_data {int dummy; } ;
struct gic_chip_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int gic_get_clocks (struct device*,struct gic_clk_data const*) ; 
 int gic_of_init_child (struct device*,struct gic_chip_data**,int) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gic_clk_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gic_chip_data*) ; 
 int /*<<< orphan*/  pm_clk_destroy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static int gic_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct gic_clk_data *data;
	struct gic_chip_data *gic;
	int ret, irq;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_err(&pdev->dev, "no device match found\n");
		return -ENODEV;
	}

	irq = irq_of_parse_and_map(dev->of_node, 0);
	if (!irq) {
		dev_err(dev, "no parent interrupt found!\n");
		return -EINVAL;
	}

	ret = gic_get_clocks(dev, data);
	if (ret)
		goto irq_dispose;

	pm_runtime_enable(dev);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		goto rpm_disable;

	ret = gic_of_init_child(dev, &gic, irq);
	if (ret)
		goto rpm_put;

	platform_set_drvdata(pdev, gic);

	pm_runtime_put(dev);

	dev_info(dev, "GIC IRQ controller registered\n");

	return 0;

rpm_put:
	pm_runtime_put_sync(dev);
rpm_disable:
	pm_runtime_disable(dev);
	pm_clk_destroy(dev);
irq_dispose:
	irq_dispose_mapping(irq);

	return ret;
}