#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct gpio_chip {char* label; int /*<<< orphan*/  of_node; scalar_t__ base; TYPE_3__* parent; int /*<<< orphan*/  ngpio; } ;
struct ocelot_pinctrl {TYPE_2__* dev; TYPE_1__* desc; struct gpio_chip gpio_chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  npins; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int devm_gpiochip_add_data (TYPE_3__*,struct gpio_chip*,struct ocelot_pinctrl*) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_chip ocelot_gpiolib_chip ; 
 int /*<<< orphan*/  ocelot_irq_handler ; 
 int /*<<< orphan*/  ocelot_irqchip ; 

__attribute__((used)) static int ocelot_gpiochip_register(struct platform_device *pdev,
				    struct ocelot_pinctrl *info)
{
	struct gpio_chip *gc;
	int ret, irq;

	info->gpio_chip = ocelot_gpiolib_chip;

	gc = &info->gpio_chip;
	gc->ngpio = info->desc->npins;
	gc->parent = &pdev->dev;
	gc->base = 0;
	gc->of_node = info->dev->of_node;
	gc->label = "ocelot-gpio";

	ret = devm_gpiochip_add_data(&pdev->dev, gc, info);
	if (ret)
		return ret;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq <= 0)
		return irq;

	ret = gpiochip_irqchip_add(gc, &ocelot_irqchip, 0, handle_edge_irq,
				   IRQ_TYPE_NONE);
	if (ret)
		return ret;

	gpiochip_set_chained_irqchip(gc, &ocelot_irqchip, irq,
				     ocelot_irq_handler);

	return 0;
}