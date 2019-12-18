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
 int /*<<< orphan*/  MV88E6XXX_G1_MAC_01 ; 
 int /*<<< orphan*/  MV88E6XXX_G1_MAC_23 ; 
 int /*<<< orphan*/  MV88E6XXX_G1_MAC_45 ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_g1_set_switch_mac(struct mv88e6xxx_chip *chip, u8 *addr)
{
	u16 reg;
	int err;

	reg = (addr[0] << 8) | addr[1];
	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_MAC_01, reg);
	if (err)
		return err;

	reg = (addr[2] << 8) | addr[3];
	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_MAC_23, reg);
	if (err)
		return err;

	reg = (addr[4] << 8) | addr[5];
	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_MAC_45, reg);
	if (err)
		return err;

	return 0;
}