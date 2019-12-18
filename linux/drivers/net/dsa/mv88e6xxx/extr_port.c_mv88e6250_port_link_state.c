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
typedef  int u16 ;
struct phylink_link_state {int link; int an_enabled; int an_complete; int /*<<< orphan*/  interface; void* duplex; void* speed; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 void* DUPLEX_UNKNOWN ; 
 int MV88E6250_PORT_STS_LINK ; 
 int MV88E6250_PORT_STS_PORTMODE_MASK ; 
#define  MV88E6250_PORT_STS_PORTMODE_MII_100_FULL 135 
#define  MV88E6250_PORT_STS_PORTMODE_MII_100_HALF 134 
#define  MV88E6250_PORT_STS_PORTMODE_MII_10_FULL 133 
#define  MV88E6250_PORT_STS_PORTMODE_MII_10_HALF 132 
#define  MV88E6250_PORT_STS_PORTMODE_PHY_100_FULL 131 
#define  MV88E6250_PORT_STS_PORTMODE_PHY_100_HALF 130 
#define  MV88E6250_PORT_STS_PORTMODE_PHY_10_FULL 129 
#define  MV88E6250_PORT_STS_PORTMODE_PHY_10_HALF 128 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_NA ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 void* SPEED_UNKNOWN ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 

int mv88e6250_port_link_state(struct mv88e6xxx_chip *chip, int port,
			      struct phylink_link_state *state)
{
	int err;
	u16 reg;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_STS, &reg);
	if (err)
		return err;

	if (port < 5) {
		switch (reg & MV88E6250_PORT_STS_PORTMODE_MASK) {
		case MV88E6250_PORT_STS_PORTMODE_PHY_10_HALF:
			state->speed = SPEED_10;
			state->duplex = DUPLEX_HALF;
			break;
		case MV88E6250_PORT_STS_PORTMODE_PHY_100_HALF:
			state->speed = SPEED_100;
			state->duplex = DUPLEX_HALF;
			break;
		case MV88E6250_PORT_STS_PORTMODE_PHY_10_FULL:
			state->speed = SPEED_10;
			state->duplex = DUPLEX_FULL;
			break;
		case MV88E6250_PORT_STS_PORTMODE_PHY_100_FULL:
			state->speed = SPEED_100;
			state->duplex = DUPLEX_FULL;
			break;
		default:
			state->speed = SPEED_UNKNOWN;
			state->duplex = DUPLEX_UNKNOWN;
			break;
		}
	} else {
		switch (reg & MV88E6250_PORT_STS_PORTMODE_MASK) {
		case MV88E6250_PORT_STS_PORTMODE_MII_10_HALF:
			state->speed = SPEED_10;
			state->duplex = DUPLEX_HALF;
			break;
		case MV88E6250_PORT_STS_PORTMODE_MII_100_HALF:
			state->speed = SPEED_100;
			state->duplex = DUPLEX_HALF;
			break;
		case MV88E6250_PORT_STS_PORTMODE_MII_10_FULL:
			state->speed = SPEED_10;
			state->duplex = DUPLEX_FULL;
			break;
		case MV88E6250_PORT_STS_PORTMODE_MII_100_FULL:
			state->speed = SPEED_100;
			state->duplex = DUPLEX_FULL;
			break;
		default:
			state->speed = SPEED_UNKNOWN;
			state->duplex = DUPLEX_UNKNOWN;
			break;
		}
	}

	state->link = !!(reg & MV88E6250_PORT_STS_LINK);
	state->an_enabled = 1;
	state->an_complete = state->link;
	state->interface = PHY_INTERFACE_MODE_NA;

	return 0;
}