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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LINK_FORCED_DOWN 130 
#define  LINK_FORCED_UP 129 
#define  LINK_UNFORCED 128 
 int /*<<< orphan*/  MV88E6XXX_PORT_MAC_CTL ; 
 int MV88E6XXX_PORT_MAC_CTL_FORCE_LINK ; 
 int MV88E6XXX_PORT_MAC_CTL_LINK_UP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_port_set_link(struct mv88e6xxx_chip *chip, int port, int link)
{
	u16 reg;
	int err;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	if (err)
		return err;

	reg &= ~(MV88E6XXX_PORT_MAC_CTL_FORCE_LINK |
		 MV88E6XXX_PORT_MAC_CTL_LINK_UP);

	switch (link) {
	case LINK_FORCED_DOWN:
		reg |= MV88E6XXX_PORT_MAC_CTL_FORCE_LINK;
		break;
	case LINK_FORCED_UP:
		reg |= MV88E6XXX_PORT_MAC_CTL_FORCE_LINK |
			MV88E6XXX_PORT_MAC_CTL_LINK_UP;
		break;
	case LINK_UNFORCED:
		/* normal link detection */
		break;
	default:
		return -EINVAL;
	}

	err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	if (err)
		return err;

	dev_dbg(chip->dev, "p%d: %s link %s\n", port,
		reg & MV88E6XXX_PORT_MAC_CTL_FORCE_LINK ? "Force" : "Unforce",
		reg & MV88E6XXX_PORT_MAC_CTL_LINK_UP ? "up" : "down");

	return 0;
}