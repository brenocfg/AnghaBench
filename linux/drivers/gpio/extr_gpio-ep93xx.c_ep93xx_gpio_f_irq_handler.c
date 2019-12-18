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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int EP93XX_GPIO_F_IRQ_BASE ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 

__attribute__((used)) static void ep93xx_gpio_f_irq_handler(struct irq_desc *desc)
{
	/*
	 * map discontiguous hw irq range to continuous sw irq range:
	 *
	 *  IRQ_EP93XX_GPIO{0..7}MUX -> EP93XX_GPIO_LINE_F{0..7}
	 */
	struct irq_chip *irqchip = irq_desc_get_chip(desc);
	unsigned int irq = irq_desc_get_irq(desc);
	int port_f_idx = ((irq + 1) & 7) ^ 4; /* {19..22,47..50} -> {0..7} */
	int gpio_irq = EP93XX_GPIO_F_IRQ_BASE + port_f_idx;

	chained_irq_enter(irqchip, desc);
	generic_handle_irq(gpio_irq);
	chained_irq_exit(irqchip, desc);
}