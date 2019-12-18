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
struct phylink_link_state {int link; int an_enabled; int an_complete; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  interface; } ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {int cmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_MAC_CTL ; 
 int MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK ; 
 int MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
#define  MV88E6XXX_PORT_STS_CMODE_1000BASEX 137 
#define  MV88E6XXX_PORT_STS_CMODE_2500BASEX 136 
 int MV88E6XXX_PORT_STS_CMODE_MASK ; 
#define  MV88E6XXX_PORT_STS_CMODE_RGMII 135 
#define  MV88E6XXX_PORT_STS_CMODE_RXAUI 134 
#define  MV88E6XXX_PORT_STS_CMODE_SGMII 133 
#define  MV88E6XXX_PORT_STS_CMODE_XAUI 132 
 int MV88E6XXX_PORT_STS_DUPLEX ; 
 int MV88E6XXX_PORT_STS_LINK ; 
#define  MV88E6XXX_PORT_STS_SPEED_10 131 
#define  MV88E6XXX_PORT_STS_SPEED_100 130 
#define  MV88E6XXX_PORT_STS_SPEED_1000 129 
#define  MV88E6XXX_PORT_STS_SPEED_10000 128 
 int MV88E6XXX_PORT_STS_SPEED_MASK ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_1000BASEX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_2500BASEX ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_ID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_RXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RXAUI ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 

int mv88e6352_port_link_state(struct mv88e6xxx_chip *chip, int port,
			      struct phylink_link_state *state)
{
	int err;
	u16 reg;

	switch (chip->ports[port].cmode) {
	case MV88E6XXX_PORT_STS_CMODE_RGMII:
		err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_MAC_CTL,
					  &reg);
		if (err)
			return err;

		if ((reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK) &&
		    (reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK))
			state->interface = PHY_INTERFACE_MODE_RGMII_ID;
		else if (reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK)
			state->interface = PHY_INTERFACE_MODE_RGMII_RXID;
		else if (reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK)
			state->interface = PHY_INTERFACE_MODE_RGMII_TXID;
		else
			state->interface = PHY_INTERFACE_MODE_RGMII;
		break;
	case MV88E6XXX_PORT_STS_CMODE_1000BASEX:
		state->interface = PHY_INTERFACE_MODE_1000BASEX;
		break;
	case MV88E6XXX_PORT_STS_CMODE_SGMII:
		state->interface = PHY_INTERFACE_MODE_SGMII;
		break;
	case MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		state->interface = PHY_INTERFACE_MODE_2500BASEX;
		break;
	case MV88E6XXX_PORT_STS_CMODE_XAUI:
		state->interface = PHY_INTERFACE_MODE_XAUI;
		break;
	case MV88E6XXX_PORT_STS_CMODE_RXAUI:
		state->interface = PHY_INTERFACE_MODE_RXAUI;
		break;
	default:
		/* we do not support other cmode values here */
		state->interface = PHY_INTERFACE_MODE_NA;
	}

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_STS, &reg);
	if (err)
		return err;

	switch (reg & MV88E6XXX_PORT_STS_SPEED_MASK) {
	case MV88E6XXX_PORT_STS_SPEED_10:
		state->speed = SPEED_10;
		break;
	case MV88E6XXX_PORT_STS_SPEED_100:
		state->speed = SPEED_100;
		break;
	case MV88E6XXX_PORT_STS_SPEED_1000:
		state->speed = SPEED_1000;
		break;
	case MV88E6XXX_PORT_STS_SPEED_10000:
		if ((reg & MV88E6XXX_PORT_STS_CMODE_MASK) ==
		    MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			state->speed = SPEED_2500;
		else
			state->speed = SPEED_10000;
		break;
	}

	state->duplex = reg & MV88E6XXX_PORT_STS_DUPLEX ?
			DUPLEX_FULL : DUPLEX_HALF;
	state->link = !!(reg & MV88E6XXX_PORT_STS_LINK);
	state->an_enabled = 1;
	state->an_complete = state->link;

	return 0;
}