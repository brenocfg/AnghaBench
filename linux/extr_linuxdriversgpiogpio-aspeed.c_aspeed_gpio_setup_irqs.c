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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct aspeed_gpio {int irq; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  aspeed_gpio_irq_handler ; 
 int /*<<< orphan*/  aspeed_gpio_irqchip ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int gpiochip_irqchip_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_valid_mask (struct aspeed_gpio*) ; 

__attribute__((used)) static int aspeed_gpio_setup_irqs(struct aspeed_gpio *gpio,
		struct platform_device *pdev)
{
	int rc;

	rc = platform_get_irq(pdev, 0);
	if (rc < 0)
		return rc;

	gpio->irq = rc;

	set_irq_valid_mask(gpio);

	rc = gpiochip_irqchip_add(&gpio->chip, &aspeed_gpio_irqchip,
			0, handle_bad_irq, IRQ_TYPE_NONE);
	if (rc) {
		dev_info(&pdev->dev, "Could not add irqchip\n");
		return rc;
	}

	gpiochip_set_chained_irqchip(&gpio->chip, &aspeed_gpio_irqchip,
				     gpio->irq, aspeed_gpio_irq_handler);

	return 0;
}