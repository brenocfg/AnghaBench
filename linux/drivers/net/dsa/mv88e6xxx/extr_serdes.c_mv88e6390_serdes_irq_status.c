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
typedef  int u8 ;
typedef  int u16 ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int cmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MV88E6390_SGMII_INT_LINK_DOWN ; 
 int MV88E6390_SGMII_INT_LINK_UP ; 
#define  MV88E6XXX_PORT_STS_CMODE_1000BASEX 130 
#define  MV88E6XXX_PORT_STS_CMODE_2500BASEX 129 
#define  MV88E6XXX_PORT_STS_CMODE_SGMII 128 
 int /*<<< orphan*/  mv88e6390_serdes_irq_link_sgmii (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6390_serdes_irq_status_sgmii (struct mv88e6xxx_chip*,int,int*) ; 

irqreturn_t mv88e6390_serdes_irq_status(struct mv88e6xxx_chip *chip, int port,
					u8 lane)
{
	u8 cmode = chip->ports[port].cmode;
	irqreturn_t ret = IRQ_NONE;
	u16 status;
	int err;

	switch (cmode) {
	case MV88E6XXX_PORT_STS_CMODE_SGMII:
	case MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	case MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		err = mv88e6390_serdes_irq_status_sgmii(chip, lane, &status);
		if (err)
			return ret;
		if (status & (MV88E6390_SGMII_INT_LINK_DOWN |
			      MV88E6390_SGMII_INT_LINK_UP)) {
			ret = IRQ_HANDLED;
			mv88e6390_serdes_irq_link_sgmii(chip, port, lane);
		}
	}

	return ret;
}