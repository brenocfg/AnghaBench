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
struct fusb302_chip {int irq_suspended; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  irq_lock; } ;
struct device {struct fusb302_chip* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fusb302_pm_suspend(struct device *dev)
{
	struct fusb302_chip *chip = dev->driver_data;
	unsigned long flags;

	spin_lock_irqsave(&chip->irq_lock, flags);
	chip->irq_suspended = true;
	spin_unlock_irqrestore(&chip->irq_lock, flags);

	/* Make sure any pending irq_work is finished before the bus suspends */
	flush_work(&chip->irq_work);
	return 0;
}