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
struct TYPE_2__ {int /*<<< orphan*/  masked; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; TYPE_1__ g2_irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mv88e6xxx_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int mv88e6xxx_g2_int_mask (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_g2_irq_bus_sync_unlock(struct irq_data *d)
{
	struct mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	int err;

	err = mv88e6xxx_g2_int_mask(chip, ~chip->g2_irq.masked);
	if (err)
		dev_err(chip->dev, "failed to mask interrupts\n");

	mv88e6xxx_reg_unlock(chip);
}