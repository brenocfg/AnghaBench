#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {TYPE_1__* watchdog_ops; } ;
struct TYPE_5__ {TYPE_3__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_action ) (struct mv88e6xxx_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static irqreturn_t mv88e6xxx_g2_watchdog_thread_fn(int irq, void *dev_id)
{
	struct mv88e6xxx_chip *chip = dev_id;
	irqreturn_t ret = IRQ_NONE;

	mutex_lock(&chip->reg_lock);
	if (chip->info->ops->watchdog_ops->irq_action)
		ret = chip->info->ops->watchdog_ops->irq_action(chip, irq);
	mutex_unlock(&chip->reg_lock);

	return ret;
}