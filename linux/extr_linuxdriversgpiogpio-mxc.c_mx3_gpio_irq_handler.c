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
typedef  int u32 ;
struct mxc_gpio_port {scalar_t__ base; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_IMR ; 
 scalar_t__ GPIO_ISR ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct mxc_gpio_port* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  mxc_gpio_irq_handler (struct mxc_gpio_port*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void mx3_gpio_irq_handler(struct irq_desc *desc)
{
	u32 irq_stat;
	struct mxc_gpio_port *port = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);

	irq_stat = readl(port->base + GPIO_ISR) & readl(port->base + GPIO_IMR);

	mxc_gpio_irq_handler(port, irq_stat);

	chained_irq_exit(chip, desc);
}