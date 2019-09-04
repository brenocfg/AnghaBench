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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int EINVAL ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL0 ; 
 int MV88E6XXX_PORT_CTL0_STATE_BLOCKING ; 
 int MV88E6XXX_PORT_CTL0_STATE_DISABLED ; 
 int MV88E6XXX_PORT_CTL0_STATE_FORWARDING ; 
 int MV88E6XXX_PORT_CTL0_STATE_LEARNING ; 
 int MV88E6XXX_PORT_CTL0_STATE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * mv88e6xxx_port_state_names ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_port_set_state(struct mv88e6xxx_chip *chip, int port, u8 state)
{
	u16 reg;
	int err;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	if (err)
		return err;

	reg &= ~MV88E6XXX_PORT_CTL0_STATE_MASK;

	switch (state) {
	case BR_STATE_DISABLED:
		state = MV88E6XXX_PORT_CTL0_STATE_DISABLED;
		break;
	case BR_STATE_BLOCKING:
	case BR_STATE_LISTENING:
		state = MV88E6XXX_PORT_CTL0_STATE_BLOCKING;
		break;
	case BR_STATE_LEARNING:
		state = MV88E6XXX_PORT_CTL0_STATE_LEARNING;
		break;
	case BR_STATE_FORWARDING:
		state = MV88E6XXX_PORT_CTL0_STATE_FORWARDING;
		break;
	default:
		return -EINVAL;
	}

	reg |= state;

	err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_CTL0, reg);
	if (err)
		return err;

	dev_dbg(chip->dev, "p%d: PortState set to %s\n", port,
		mv88e6xxx_port_state_names[state]);

	return 0;
}