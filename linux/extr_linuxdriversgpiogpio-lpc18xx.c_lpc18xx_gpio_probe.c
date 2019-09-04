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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct lpc18xx_gpio_chip {int /*<<< orphan*/  clk; TYPE_1__ gpio; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc18xx_gpio_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct lpc18xx_gpio_chip*) ; 
 TYPE_1__ lpc18xx_chip ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_gpio_probe(struct platform_device *pdev)
{
	struct lpc18xx_gpio_chip *gc;
	struct resource *res;
	int ret;

	gc = devm_kzalloc(&pdev->dev, sizeof(*gc), GFP_KERNEL);
	if (!gc)
		return -ENOMEM;

	gc->gpio = lpc18xx_chip;
	platform_set_drvdata(pdev, gc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(gc->base))
		return PTR_ERR(gc->base);

	gc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(gc->clk)) {
		dev_err(&pdev->dev, "input clock not found\n");
		return PTR_ERR(gc->clk);
	}

	ret = clk_prepare_enable(gc->clk);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		return ret;
	}

	spin_lock_init(&gc->lock);

	gc->gpio.parent = &pdev->dev;

	ret = gpiochip_add_data(&gc->gpio, gc);
	if (ret) {
		dev_err(&pdev->dev, "failed to add gpio chip\n");
		clk_disable_unprepare(gc->clk);
		return ret;
	}

	return 0;
}