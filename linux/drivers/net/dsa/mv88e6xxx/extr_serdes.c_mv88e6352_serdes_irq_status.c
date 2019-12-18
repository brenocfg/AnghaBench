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
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MV88E6352_SERDES_INT_LINK_CHANGE ; 
 int /*<<< orphan*/  MV88E6352_SERDES_INT_STATUS ; 
 int /*<<< orphan*/  mv88e6352_serdes_irq_link (struct mv88e6xxx_chip*,int) ; 
 int mv88e6352_serdes_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 

irqreturn_t mv88e6352_serdes_irq_status(struct mv88e6xxx_chip *chip, int port,
					u8 lane)
{
	irqreturn_t ret = IRQ_NONE;
	u16 status;
	int err;

	err = mv88e6352_serdes_read(chip, MV88E6352_SERDES_INT_STATUS, &status);
	if (err)
		return ret;

	if (status & MV88E6352_SERDES_INT_LINK_CHANGE) {
		ret = IRQ_HANDLED;
		mv88e6352_serdes_irq_link(chip, port);
	}

	return ret;
}