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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_MY_PAUSE ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6185_port_set_pause(struct mv88e6xxx_chip *chip, int port,
			     int pause)
{
	u16 reg;
	int err;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_STS, &reg);
	if (err)
		return err;

	if (pause)
		reg |= MV88E6XXX_PORT_STS_MY_PAUSE;
	else
		reg &= ~MV88E6XXX_PORT_STS_MY_PAUSE;

	return mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_STS, reg);
}