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
struct mv88e6xxx_chip {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_free_common (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_g1_irq_free(struct mv88e6xxx_chip *chip)
{
	/*
	 * free_irq must be called without reg_lock taken because the irq
	 * handler takes this lock, too.
	 */
	free_irq(chip->irq, chip);

	mv88e6xxx_reg_lock(chip);
	mv88e6xxx_g1_irq_free_common(chip);
	mv88e6xxx_reg_unlock(chip);
}