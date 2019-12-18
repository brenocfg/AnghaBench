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
struct TYPE_2__ {int masked; int /*<<< orphan*/  nirqs; } ;
struct mv88e6xxx_chip {TYPE_1__ g1_irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV88E6XXX_G1_CTL1 ; 
 struct mv88e6xxx_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_g1_irq_bus_sync_unlock(struct irq_data *d)
{
	struct mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	u16 mask = GENMASK(chip->g1_irq.nirqs, 0);
	u16 reg;
	int err;

	err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_CTL1, &reg);
	if (err)
		goto out;

	reg &= ~mask;
	reg |= (~chip->g1_irq.masked & mask);

	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_CTL1, reg);
	if (err)
		goto out;

out:
	mv88e6xxx_reg_unlock(chip);
}