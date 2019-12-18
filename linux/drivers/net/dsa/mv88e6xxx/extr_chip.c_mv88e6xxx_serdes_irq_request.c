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
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_serdes_irq_enable (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 unsigned int mv88e6xxx_serdes_irq_mapping (struct mv88e6xxx_chip*,int) ; 
 int /*<<< orphan*/  mv88e6xxx_serdes_irq_thread_fn ; 
 int request_threaded_irq (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mv88e6xxx_port*) ; 

__attribute__((used)) static int mv88e6xxx_serdes_irq_request(struct mv88e6xxx_chip *chip, int port,
					u8 lane)
{
	struct mv88e6xxx_port *dev_id = &chip->ports[port];
	unsigned int irq;
	int err;

	/* Nothing to request if this SERDES port has no IRQ */
	irq = mv88e6xxx_serdes_irq_mapping(chip, port);
	if (!irq)
		return 0;

	/* Requesting the IRQ will trigger IRQ callbacks, so release the lock */
	mv88e6xxx_reg_unlock(chip);
	err = request_threaded_irq(irq, NULL, mv88e6xxx_serdes_irq_thread_fn,
				   IRQF_ONESHOT, "mv88e6xxx-serdes", dev_id);
	mv88e6xxx_reg_lock(chip);
	if (err)
		return err;

	dev_id->serdes_irq = irq;

	return mv88e6xxx_serdes_irq_enable(chip, port, lane);
}