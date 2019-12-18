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
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {int port_base_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MV88E6341_PORT_RESERVED_1A_FORCE_CMODE ; 
 int MV88E6341_PORT_RESERVED_1A_SGMII_AN ; 
 int mv88e6xxx_port_hidden_read (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_hidden_write (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6341_port_set_cmode_writable(struct mv88e6xxx_chip *chip,
					     int port)
{
	int err, addr;
	u16 reg, bits;

	if (port != 5)
		return -EOPNOTSUPP;

	addr = chip->info->port_base_addr + port;

	err = mv88e6xxx_port_hidden_read(chip, 0x7, addr, 0, &reg);
	if (err)
		return err;

	bits = MV88E6341_PORT_RESERVED_1A_FORCE_CMODE |
	       MV88E6341_PORT_RESERVED_1A_SGMII_AN;

	if ((reg & bits) == bits)
		return 0;

	reg |= bits;
	return mv88e6xxx_port_hidden_write(chip, 0x7, addr, 0, reg);
}