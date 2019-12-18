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
typedef  int /*<<< orphan*/  u8 ;
struct mv88e6xxx_port {unsigned int serdes_irq; } ;
struct mv88e6xxx_chip {struct mv88e6xxx_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (unsigned int,struct mv88e6xxx_port*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_serdes_irq_disable (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_serdes_irq_free(struct mv88e6xxx_chip *chip, int port,
				     u8 lane)
{
	struct mv88e6xxx_port *dev_id = &chip->ports[port];
	unsigned int irq = dev_id->serdes_irq;
	int err;

	/* Nothing to free if no IRQ has been requested */
	if (!irq)
		return 0;

	err = mv88e6xxx_serdes_irq_disable(chip, port, lane);

	/* Freeing the IRQ will trigger IRQ callbacks, so release the lock */
	mv88e6xxx_reg_unlock(chip);
	free_irq(irq, dev_id);
	mv88e6xxx_reg_lock(chip);

	dev_id->serdes_irq = 0;

	return err;
}