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
struct mv88e6xxx_chip {int /*<<< orphan*/  irq_poll_work; int /*<<< orphan*/  kworker; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create_worker (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int mv88e6xxx_g1_irq_setup_common (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_irq_poll ; 

__attribute__((used)) static int mv88e6xxx_irq_poll_setup(struct mv88e6xxx_chip *chip)
{
	int err;

	err = mv88e6xxx_g1_irq_setup_common(chip);
	if (err)
		return err;

	kthread_init_delayed_work(&chip->irq_poll_work,
				  mv88e6xxx_irq_poll);

	chip->kworker = kthread_create_worker(0, "%s", dev_name(chip->dev));
	if (IS_ERR(chip->kworker))
		return PTR_ERR(chip->kworker);

	kthread_queue_delayed_work(chip->kworker, &chip->irq_poll_work,
				   msecs_to_jiffies(100));

	return 0;
}