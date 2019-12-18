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
typedef  size_t u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL2 ; 
 size_t MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mv88e6xxx_port_8021q_mode_names ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,size_t*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,size_t) ; 

int mv88e6xxx_port_set_8021q_mode(struct mv88e6xxx_chip *chip, int port,
				  u16 mode)
{
	u16 reg;
	int err;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	if (err)
		return err;

	reg &= ~MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK;
	reg |= mode & MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK;

	err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_CTL2, reg);
	if (err)
		return err;

	dev_dbg(chip->dev, "p%d: 802.1QMode set to %s\n", port,
		mv88e6xxx_port_8021q_mode_names[mode]);

	return 0;
}