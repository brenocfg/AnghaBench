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
struct irq_data {int dummy; } ;
struct iproc_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct iproc_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  iproc_gpio_irq_set_mask (struct irq_data*,int) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iproc_gpio_irq_mask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct iproc_gpio *chip = gpiochip_get_data(gc);
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	iproc_gpio_irq_set_mask(d, false);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
}