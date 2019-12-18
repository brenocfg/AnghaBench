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
 int /*<<< orphan*/  MV88E6XXX_G1_IEEE_PRI ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6250_g1_ieee_pri_map(struct mv88e6xxx_chip *chip)
{
	/* Reset the IEEE Tag priorities to defaults */
	return mv88e6xxx_g1_write(chip, MV88E6XXX_G1_IEEE_PRI, 0xfa50);
}