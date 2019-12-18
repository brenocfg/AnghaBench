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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int ngpio; int base; int /*<<< orphan*/  to_irq; int /*<<< orphan*/ * parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  direction_output; } ;
struct mb86s70_gpio_chip {TYPE_1__ gc; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  acpi_gpiochip_request_interrupts (TYPE_1__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mb86s70_gpio_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct mb86s70_gpio_chip*) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb86s70_gpio_direction_input ; 
 int /*<<< orphan*/  mb86s70_gpio_direction_output ; 
 int /*<<< orphan*/  mb86s70_gpio_free ; 
 int /*<<< orphan*/  mb86s70_gpio_get ; 
 int /*<<< orphan*/  mb86s70_gpio_request ; 
 int /*<<< orphan*/  mb86s70_gpio_set ; 
 int /*<<< orphan*/  mb86s70_gpio_to_irq ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mb86s70_gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mb86s70_gpio_probe(struct platform_device *pdev)
{
	struct mb86s70_gpio_chip *gchip;
	int ret;

	gchip = devm_kzalloc(&pdev->dev, sizeof(*gchip), GFP_KERNEL);
	if (gchip == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, gchip);

	gchip->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(gchip->base))
		return PTR_ERR(gchip->base);

	if (!has_acpi_companion(&pdev->dev)) {
		gchip->clk = devm_clk_get(&pdev->dev, NULL);
		if (IS_ERR(gchip->clk))
			return PTR_ERR(gchip->clk);

		ret = clk_prepare_enable(gchip->clk);
		if (ret)
			return ret;
	}

	spin_lock_init(&gchip->lock);

	gchip->gc.direction_output = mb86s70_gpio_direction_output;
	gchip->gc.direction_input = mb86s70_gpio_direction_input;
	gchip->gc.request = mb86s70_gpio_request;
	gchip->gc.free = mb86s70_gpio_free;
	gchip->gc.get = mb86s70_gpio_get;
	gchip->gc.set = mb86s70_gpio_set;
	gchip->gc.label = dev_name(&pdev->dev);
	gchip->gc.ngpio = 32;
	gchip->gc.owner = THIS_MODULE;
	gchip->gc.parent = &pdev->dev;
	gchip->gc.base = -1;

	if (has_acpi_companion(&pdev->dev))
		gchip->gc.to_irq = mb86s70_gpio_to_irq;

	ret = gpiochip_add_data(&gchip->gc, gchip);
	if (ret) {
		dev_err(&pdev->dev, "couldn't register gpio driver\n");
		clk_disable_unprepare(gchip->clk);
		return ret;
	}

	if (has_acpi_companion(&pdev->dev))
		acpi_gpiochip_request_interrupts(&gchip->gc);

	return 0;
}