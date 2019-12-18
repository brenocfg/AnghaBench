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
struct nsp_gpio {int /*<<< orphan*/  lock; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct nsp_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  nsp_gpio_irq_set_mask (struct irq_data*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nsp_gpio_irq_unmask(struct irq_data *d)
{
	struct nsp_gpio *chip = irq_data_get_irq_chip_data(d);
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	nsp_gpio_irq_set_mask(d, true);
	raw_spin_unlock_irqrestore(&chip->lock, flags);
}