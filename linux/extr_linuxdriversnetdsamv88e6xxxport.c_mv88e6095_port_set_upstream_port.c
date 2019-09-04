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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int MV88E6095_PORT_CTL2_CPU_PORT_MASK ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL2 ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6095_port_set_upstream_port(struct mv88e6xxx_chip *chip, int port,
				     int upstream_port)
{
	int err;
	u16 reg;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	if (err)
		return err;

	reg &= ~MV88E6095_PORT_CTL2_CPU_PORT_MASK;
	reg |= upstream_port;

	return mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_CTL2, reg);
}