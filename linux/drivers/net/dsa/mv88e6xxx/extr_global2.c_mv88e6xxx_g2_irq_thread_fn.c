#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct mv88e6xxx_chip {TYPE_1__ g2_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  handle_nested_irq (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int mv88e6xxx_g2_int_source (struct mv88e6xxx_chip*,int*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static irqreturn_t mv88e6xxx_g2_irq_thread_fn(int irq, void *dev_id)
{
	struct mv88e6xxx_chip *chip = dev_id;
	unsigned int nhandled = 0;
	unsigned int sub_irq;
	unsigned int n;
	int err;
	u16 reg;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g2_int_source(chip, &reg);
	mv88e6xxx_reg_unlock(chip);
	if (err)
		goto out;

	for (n = 0; n < 16; ++n) {
		if (reg & (1 << n)) {
			sub_irq = irq_find_mapping(chip->g2_irq.domain, n);
			handle_nested_irq(sub_irq);
			++nhandled;
		}
	}
out:
	return (nhandled > 0 ? IRQ_HANDLED : IRQ_NONE);
}