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
typedef  int /*<<< orphan*/  u32 ;
struct nmk_gpio_chip {int /*<<< orphan*/  clk; scalar_t__ addr; } ;
struct irq_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NMK_GPIO_IS ; 
 int /*<<< orphan*/  __nmk_gpio_irq_handler (struct irq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void nmk_gpio_irq_handler(struct irq_desc *desc)
{
	struct gpio_chip *chip = irq_desc_get_handler_data(desc);
	struct nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	u32 status;

	clk_enable(nmk_chip->clk);
	status = readl(nmk_chip->addr + NMK_GPIO_IS);
	clk_disable(nmk_chip->clk);

	__nmk_gpio_irq_handler(desc, status);
}