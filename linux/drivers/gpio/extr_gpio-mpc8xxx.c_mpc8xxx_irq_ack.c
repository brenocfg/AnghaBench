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
struct gpio_chip {int /*<<< orphan*/  (* write_reg ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct mpc8xxx_gpio_chip {scalar_t__ regs; struct gpio_chip gc; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_IER ; 
 struct mpc8xxx_gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  mpc_pin2mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc8xxx_irq_ack(struct irq_data *d)
{
	struct mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	struct gpio_chip *gc = &mpc8xxx_gc->gc;

	gc->write_reg(mpc8xxx_gc->regs + GPIO_IER,
		      mpc_pin2mask(irqd_to_hwirq(d)));
}