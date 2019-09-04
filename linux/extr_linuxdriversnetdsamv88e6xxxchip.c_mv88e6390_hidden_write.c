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
 int /*<<< orphan*/  PORT_RESERVED_1A ; 
 int PORT_RESERVED_1A_BLOCK ; 
 int PORT_RESERVED_1A_BUSY ; 
 int /*<<< orphan*/  PORT_RESERVED_1A_CTRL_PORT ; 
 int /*<<< orphan*/  PORT_RESERVED_1A_DATA_PORT ; 
 int PORT_RESERVED_1A_PORT_SHIFT ; 
 int PORT_RESERVED_1A_WRITE ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6390_hidden_write(struct mv88e6xxx_chip *chip, int port,
				  int reg, u16 val)
{
	u16 ctrl;
	int err;

	err = mv88e6xxx_port_write(chip, PORT_RESERVED_1A_DATA_PORT,
				   PORT_RESERVED_1A, val);
	if (err)
		return err;

	ctrl = PORT_RESERVED_1A_BUSY | PORT_RESERVED_1A_WRITE |
	       PORT_RESERVED_1A_BLOCK | port << PORT_RESERVED_1A_PORT_SHIFT |
	       reg;

	return mv88e6xxx_port_write(chip, PORT_RESERVED_1A_CTRL_PORT,
				    PORT_RESERVED_1A, ctrl);
}