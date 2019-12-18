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
 int /*<<< orphan*/  MV88E6XXX_G2_MISC ; 
 int /*<<< orphan*/  MV88E6XXX_G2_MISC_5_BIT_PORT ; 
 int mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_g2_misc_5_bit_port(struct mv88e6xxx_chip *chip,
					bool port_5_bit)
{
	u16 val;
	int err;

	err = mv88e6xxx_g2_read(chip, MV88E6XXX_G2_MISC, &val);
	if (err)
		return err;

	if (port_5_bit)
		val |= MV88E6XXX_G2_MISC_5_BIT_PORT;
	else
		val &= ~MV88E6XXX_G2_MISC_5_BIT_PORT;

	return mv88e6xxx_g2_write(chip, MV88E6XXX_G2_MISC, val);
}