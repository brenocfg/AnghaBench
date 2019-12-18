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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; struct dsa_switch* ds; TYPE_1__* ports; } ;
struct dsa_switch {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_2__ {int cmode; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int DUPLEX_UNKNOWN ; 
 int LINK_FORCED_DOWN ; 
 int LINK_FORCED_UP ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MV88E6390_SGMII_PHY_STATUS ; 
 int MV88E6390_SGMII_PHY_STATUS_DUPLEX_FULL ; 
 int MV88E6390_SGMII_PHY_STATUS_LINK ; 
 int MV88E6390_SGMII_PHY_STATUS_SPD_DPL_VALID ; 
#define  MV88E6390_SGMII_PHY_STATUS_SPEED_10 133 
#define  MV88E6390_SGMII_PHY_STATUS_SPEED_100 132 
#define  MV88E6390_SGMII_PHY_STATUS_SPEED_1000 131 
 int MV88E6390_SGMII_PHY_STATUS_SPEED_MASK ; 
#define  MV88E6XXX_PORT_STS_CMODE_1000BASEX 130 
#define  MV88E6XXX_PORT_STS_CMODE_2500BASEX 129 
#define  MV88E6XXX_PORT_STS_CMODE_SGMII 128 
 int /*<<< orphan*/  PAUSE_OFF ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_1000BASEX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_2500BASEX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_2500 ; 
 int SPEED_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_change (struct dsa_switch*,int,int) ; 
 int mv88e6390_serdes_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_setup_mac (struct mv88e6xxx_chip*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6390_serdes_irq_link_sgmii(struct mv88e6xxx_chip *chip,
					    int port, u8 lane)
{
	u8 cmode = chip->ports[port].cmode;
	struct dsa_switch *ds = chip->ds;
	int duplex = DUPLEX_UNKNOWN;
	int speed = SPEED_UNKNOWN;
	phy_interface_t mode;
	int link, err;
	u16 status;

	err = mv88e6390_serdes_read(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_PHY_STATUS, &status);
	if (err) {
		dev_err(chip->dev, "can't read SGMII PHY status: %d\n", err);
		return;
	}

	link = status & MV88E6390_SGMII_PHY_STATUS_LINK ?
	       LINK_FORCED_UP : LINK_FORCED_DOWN;

	if (status & MV88E6390_SGMII_PHY_STATUS_SPD_DPL_VALID) {
		duplex = status & MV88E6390_SGMII_PHY_STATUS_DUPLEX_FULL ?
			 DUPLEX_FULL : DUPLEX_HALF;

		switch (status & MV88E6390_SGMII_PHY_STATUS_SPEED_MASK) {
		case MV88E6390_SGMII_PHY_STATUS_SPEED_1000:
			if (cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
				speed = SPEED_2500;
			else
				speed = SPEED_1000;
			break;
		case MV88E6390_SGMII_PHY_STATUS_SPEED_100:
			speed = SPEED_100;
			break;
		case MV88E6390_SGMII_PHY_STATUS_SPEED_10:
			speed = SPEED_10;
			break;
		default:
			dev_err(chip->dev, "invalid PHY speed\n");
			return;
		}
	}

	switch (cmode) {
	case MV88E6XXX_PORT_STS_CMODE_SGMII:
		mode = PHY_INTERFACE_MODE_SGMII;
		break;
	case MV88E6XXX_PORT_STS_CMODE_1000BASEX:
		mode = PHY_INTERFACE_MODE_1000BASEX;
		break;
	case MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		mode = PHY_INTERFACE_MODE_2500BASEX;
		break;
	default:
		mode = PHY_INTERFACE_MODE_NA;
	}

	err = mv88e6xxx_port_setup_mac(chip, port, link, speed, duplex,
				       PAUSE_OFF, mode);
	if (err)
		dev_err(chip->dev, "can't propagate PHY settings to MAC: %d\n",
			err);
	else
		dsa_port_phylink_mac_change(ds, port, link == LINK_FORCED_UP);
}