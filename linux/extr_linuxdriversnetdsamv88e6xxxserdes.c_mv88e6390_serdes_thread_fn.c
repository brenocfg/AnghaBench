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
typedef  int u8 ;
typedef  int u16 ;
struct mv88e6xxx_port {int cmode; int /*<<< orphan*/  port; struct mv88e6xxx_chip* chip; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MV88E6390_SGMII_INT_LINK_DOWN ; 
 int MV88E6390_SGMII_INT_LINK_UP ; 
#define  MV88E6XXX_PORT_STS_CMODE_1000BASE_X 130 
#define  MV88E6XXX_PORT_STS_CMODE_2500BASEX 129 
#define  MV88E6XXX_PORT_STS_CMODE_SGMII 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6390_serdes_irq_link_sgmii (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int mv88e6390_serdes_irq_status_sgmii (struct mv88e6xxx_chip*,int,int*) ; 
 int mv88e6390x_serdes_get_lane (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mv88e6390_serdes_thread_fn(int irq, void *dev_id)
{
	struct mv88e6xxx_port *port = dev_id;
	struct mv88e6xxx_chip *chip = port->chip;
	irqreturn_t ret = IRQ_NONE;
	u8 cmode = port->cmode;
	u16 status;
	int lane;
	int err;

	lane = mv88e6390x_serdes_get_lane(chip, port->port);

	mutex_lock(&chip->reg_lock);

	switch (cmode) {
	case MV88E6XXX_PORT_STS_CMODE_SGMII:
	case MV88E6XXX_PORT_STS_CMODE_1000BASE_X:
	case MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		err = mv88e6390_serdes_irq_status_sgmii(chip, lane, &status);
		if (err)
			goto out;
		if (status & (MV88E6390_SGMII_INT_LINK_DOWN |
			      MV88E6390_SGMII_INT_LINK_UP)) {
			ret = IRQ_HANDLED;
			mv88e6390_serdes_irq_link_sgmii(chip, port->port, lane);
		}
	}
out:
	mutex_unlock(&chip->reg_lock);

	return ret;
}