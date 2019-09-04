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
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
typedef  int phy_interface_t ;
struct TYPE_2__ {int cmode; scalar_t__ serdes_irq; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
 int MV88E6XXX_PORT_STS_CMODE_1000BASE_X ; 
 int MV88E6XXX_PORT_STS_CMODE_2500BASEX ; 
 int MV88E6XXX_PORT_STS_CMODE_MASK ; 
 int MV88E6XXX_PORT_STS_CMODE_RXAUI ; 
 int MV88E6XXX_PORT_STS_CMODE_SGMII ; 
 int MV88E6XXX_PORT_STS_CMODE_XAUI ; 
#define  PHY_INTERFACE_MODE_1000BASEX 133 
#define  PHY_INTERFACE_MODE_2500BASEX 132 
 int PHY_INTERFACE_MODE_NA ; 
#define  PHY_INTERFACE_MODE_RXAUI 131 
#define  PHY_INTERFACE_MODE_SGMII 130 
#define  PHY_INTERFACE_MODE_XAUI 129 
#define  PHY_INTERFACE_MODE_XGMII 128 
 int mv88e6390_serdes_irq_disable (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6390_serdes_irq_enable (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6390x_serdes_get_lane (struct mv88e6xxx_chip*,int) ; 
 int mv88e6390x_serdes_power (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6390x_port_set_cmode(struct mv88e6xxx_chip *chip, int port,
			      phy_interface_t mode)
{
	int lane;
	u16 cmode;
	u16 reg;
	int err;

	if (mode == PHY_INTERFACE_MODE_NA)
		return 0;

	if (port != 9 && port != 10)
		return -EOPNOTSUPP;

	switch (mode) {
	case PHY_INTERFACE_MODE_1000BASEX:
		cmode = MV88E6XXX_PORT_STS_CMODE_1000BASE_X;
		break;
	case PHY_INTERFACE_MODE_SGMII:
		cmode = MV88E6XXX_PORT_STS_CMODE_SGMII;
		break;
	case PHY_INTERFACE_MODE_2500BASEX:
		cmode = MV88E6XXX_PORT_STS_CMODE_2500BASEX;
		break;
	case PHY_INTERFACE_MODE_XGMII:
	case PHY_INTERFACE_MODE_XAUI:
		cmode = MV88E6XXX_PORT_STS_CMODE_XAUI;
		break;
	case PHY_INTERFACE_MODE_RXAUI:
		cmode = MV88E6XXX_PORT_STS_CMODE_RXAUI;
		break;
	default:
		cmode = 0;
	}

	/* cmode doesn't change, nothing to do for us */
	if (cmode == chip->ports[port].cmode)
		return 0;

	lane = mv88e6390x_serdes_get_lane(chip, port);
	if (lane < 0)
		return lane;

	if (chip->ports[port].serdes_irq) {
		err = mv88e6390_serdes_irq_disable(chip, port, lane);
		if (err)
			return err;
	}

	err = mv88e6390x_serdes_power(chip, port, false);
	if (err)
		return err;

	if (cmode) {
		err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_STS, &reg);
		if (err)
			return err;

		reg &= ~MV88E6XXX_PORT_STS_CMODE_MASK;
		reg |= cmode;

		err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_STS, reg);
		if (err)
			return err;

		err = mv88e6390x_serdes_power(chip, port, true);
		if (err)
			return err;

		if (chip->ports[port].serdes_irq) {
			err = mv88e6390_serdes_irq_enable(chip, port, lane);
			if (err)
				return err;
		}
	}

	chip->ports[port].cmode = cmode;

	return 0;
}