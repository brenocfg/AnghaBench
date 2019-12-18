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
struct timbgpio {int irq_base; unsigned long last_ier; int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct irq_data {int irq; } ;

/* Variables and functions */
 scalar_t__ TGPIO_IER ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 
 struct timbgpio* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void timbgpio_irq_disable(struct irq_data *d)
{
	struct timbgpio *tgpio = irq_data_get_irq_chip_data(d);
	int offset = d->irq - tgpio->irq_base;
	unsigned long flags;

	spin_lock_irqsave(&tgpio->lock, flags);
	tgpio->last_ier &= ~(1UL << offset);
	iowrite32(tgpio->last_ier, tgpio->membase + TGPIO_IER);
	spin_unlock_irqrestore(&tgpio->lock, flags);
}