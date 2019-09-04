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

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_GPIO_LINE_MAX_IRQ ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO0MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO1MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO2MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO3MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO4MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO5MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO6MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO7MUX ; 
 int /*<<< orphan*/  IRQ_EP93XX_GPIO_AB ; 
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 int /*<<< orphan*/  ep93xx_gpio_ab_irq_handler ; 
 int /*<<< orphan*/  ep93xx_gpio_f_irq_handler ; 
 int /*<<< orphan*/  ep93xx_gpio_irq_chip ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_gpio_init_irq(void)
{
	int gpio_irq;

	for (gpio_irq = gpio_to_irq(0);
	     gpio_irq <= gpio_to_irq(EP93XX_GPIO_LINE_MAX_IRQ); ++gpio_irq) {
		irq_set_chip_and_handler(gpio_irq, &ep93xx_gpio_irq_chip,
					 handle_level_irq);
		irq_clear_status_flags(gpio_irq, IRQ_NOREQUEST);
	}

	irq_set_chained_handler(IRQ_EP93XX_GPIO_AB,
				ep93xx_gpio_ab_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO0MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO1MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO2MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO3MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO4MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO5MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO6MUX,
				ep93xx_gpio_f_irq_handler);
	irq_set_chained_handler(IRQ_EP93XX_GPIO7MUX,
				ep93xx_gpio_f_irq_handler);
}