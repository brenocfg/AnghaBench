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
struct gpio_chip {int (* read_reg ) (scalar_t__) ;int /*<<< orphan*/  (* write_reg ) (scalar_t__,int) ;} ;
struct mpc8xxx_gpio_chip {int /*<<< orphan*/  lock; scalar_t__ regs; struct gpio_chip gc; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_IMR ; 
 struct mpc8xxx_gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int mpc_pin2mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int stub2 (scalar_t__) ; 

__attribute__((used)) static void mpc8xxx_irq_unmask(struct irq_data *d)
{
	struct mpc8xxx_gpio_chip *mpc8xxx_gc = irq_data_get_irq_chip_data(d);
	struct gpio_chip *gc = &mpc8xxx_gc->gc;
	unsigned long flags;

	raw_spin_lock_irqsave(&mpc8xxx_gc->lock, flags);

	gc->write_reg(mpc8xxx_gc->regs + GPIO_IMR,
		gc->read_reg(mpc8xxx_gc->regs + GPIO_IMR)
		| mpc_pin2mask(irqd_to_hwirq(d)));

	raw_spin_unlock_irqrestore(&mpc8xxx_gc->lock, flags);
}