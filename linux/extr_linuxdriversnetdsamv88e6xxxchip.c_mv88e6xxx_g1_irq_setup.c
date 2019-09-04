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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_lockdep_class (int /*<<< orphan*/ ,struct lock_class_key*,struct lock_class_key*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_free_common (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_irq_setup_common (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_thread_fn ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_g1_irq_setup(struct mv88e6xxx_chip *chip)
{
	static struct lock_class_key lock_key;
	static struct lock_class_key request_key;
	int err;

	err = mv88e6xxx_g1_irq_setup_common(chip);
	if (err)
		return err;

	/* These lock classes tells lockdep that global 1 irqs are in
	 * a different category than their parent GPIO, so it won't
	 * report false recursion.
	 */
	irq_set_lockdep_class(chip->irq, &lock_key, &request_key);

	err = request_threaded_irq(chip->irq, NULL,
				   mv88e6xxx_g1_irq_thread_fn,
				   IRQF_ONESHOT,
				   dev_name(chip->dev), chip);
	if (err)
		mv88e6xxx_g1_irq_free_common(chip);

	return err;
}