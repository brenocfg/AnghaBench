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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_PORT_RESERVED_1A ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_RESERVED_1A_BUSY ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT ; 
 int __bf_shf (int /*<<< orphan*/ ) ; 
 int mv88e6xxx_wait_bit (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mv88e6xxx_port_hidden_wait(struct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_PORT_RESERVED_1A_BUSY);

	return mv88e6xxx_wait_bit(chip, MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT,
				  MV88E6XXX_PORT_RESERVED_1A, bit, 0);
}