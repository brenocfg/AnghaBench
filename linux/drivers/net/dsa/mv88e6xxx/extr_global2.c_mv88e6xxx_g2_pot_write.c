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
 int /*<<< orphan*/  MV88E6XXX_G2_PRIO_OVERRIDE ; 
 int MV88E6XXX_G2_PRIO_OVERRIDE_UPDATE ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_g2_pot_write(struct mv88e6xxx_chip *chip, int pointer,
				  u8 data)
{
	u16 val = (pointer << 8) | (data & 0x7);

	return mv88e6xxx_g2_write(chip, MV88E6XXX_G2_PRIO_OVERRIDE,
				  MV88E6XXX_G2_PRIO_OVERRIDE_UPDATE | val);
}