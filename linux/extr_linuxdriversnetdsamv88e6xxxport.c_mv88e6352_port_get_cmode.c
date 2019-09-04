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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_PORT_STS ; 
 int MV88E6XXX_PORT_STS_CMODE_MASK ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 

int mv88e6352_port_get_cmode(struct mv88e6xxx_chip *chip, int port, u8 *cmode)
{
	int err;
	u16 reg;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_STS, &reg);
	if (err)
		return err;

	*cmode = reg & MV88E6XXX_PORT_STS_CMODE_MASK;

	return 0;
}