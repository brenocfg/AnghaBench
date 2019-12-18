#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {struct device* parent; } ;
struct lpc18xx_gpio_chip {int /*<<< orphan*/  clk; TYPE_1__ gpio; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct lpc18xx_gpio_chip*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct lpc18xx_gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__ lpc18xx_chip ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic_probe (struct lpc18xx_gpio_chip*) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int,struct resource*) ; 
 int of_property_match_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct lpc18xx_gpio_chip *gc;
	int index, ret;

	gc = devm_kzalloc(dev, sizeof(*gc), GFP_KERNEL);
	if (!gc)
		return -ENOMEM;

	gc->gpio = lpc18xx_chip;
	platform_set_drvdata(pdev, gc);

	index = of_property_match_string(dev->of_node, "reg-names", "gpio");
	if (index < 0) {
		/* To support backward compatibility take the first resource */
		gc->base = devm_platform_ioremap_resource(pdev, 0);
	} else {
		struct resource res;

		ret = of_address_to_resource(dev->of_node, index, &res);
		if (ret < 0)
			return ret;

		gc->base = devm_ioremap_resource(dev, &res);
	}
	if (IS_ERR(gc->base))
		return PTR_ERR(gc->base);

	gc->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(gc->clk)) {
		dev_err(dev, "input clock not found\n");
		return PTR_ERR(gc->clk);
	}

	ret = clk_prepare_enable(gc->clk);
	if (ret) {
		dev_err(dev, "unable to enable clock\n");
		return ret;
	}

	spin_lock_init(&gc->lock);

	gc->gpio.parent = dev;

	ret = devm_gpiochip_add_data(dev, &gc->gpio, gc);
	if (ret) {
		dev_err(dev, "failed to add gpio chip\n");
		clk_disable_unprepare(gc->clk);
		return ret;
	}

	/* On error GPIO pin interrupt controller just won't be registered */
	lpc18xx_gpio_pin_ic_probe(gc);

	return 0;
}