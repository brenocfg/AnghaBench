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
struct fusb302_chip {int irq_while_suspended; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_work; scalar_t__ irq_suspended; int /*<<< orphan*/  gpio_int_n_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t fusb302_irq_intn(int irq, void *dev_id)
{
	struct fusb302_chip *chip = dev_id;
	unsigned long flags;

	/* Disable our level triggered IRQ until our irq_work has cleared it */
	disable_irq_nosync(chip->gpio_int_n_irq);

	spin_lock_irqsave(&chip->irq_lock, flags);
	if (chip->irq_suspended)
		chip->irq_while_suspended = true;
	else
		schedule_work(&chip->irq_work);
	spin_unlock_irqrestore(&chip->irq_lock, flags);

	return IRQ_HANDLED;
}