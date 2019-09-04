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
struct phylink_link_state {int link; int an_enabled; int an_complete; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
 int MV88E6XXX_PORT_STS_CMODE_2500BASEX ; 
 int MV88E6XXX_PORT_STS_CMODE_MASK ; 
 int MV88E6XXX_PORT_STS_DUPLEX ; 
 int MV88E6XXX_PORT_STS_LINK ; 
#define  MV88E6XXX_PORT_STS_SPEED_10 131 
#define  MV88E6XXX_PORT_STS_SPEED_100 130 
#define  MV88E6XXX_PORT_STS_SPEED_1000 129 
#define  MV88E6XXX_PORT_STS_SPEED_10000 128 
 int MV88E6XXX_PORT_STS_SPEED_MASK ; 
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