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
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  kworker; int /*<<< orphan*/  irq_poll_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_free_common (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_irq_poll_free(struct mv88e6xxx_chip *chip)
{
	kthread_cancel_delayed_work_sync(&chip->irq_poll_work);
	kthread_destroy_worker(chip->kworker);

	mutex_lock(&chip->reg_lock);
	mv88e6xxx_g1_irq_free_common(chip);
	mutex_unlock(&chip->reg_lock);
}