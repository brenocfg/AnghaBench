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
 int /*<<< orphan*/  MV88E6XXX_G2_EEPROM_CMD ; 
 int /*<<< orphan*/  MV88E6XXX_G2_EEPROM_CMD_BUSY ; 
 int /*<<< orphan*/  MV88E6XXX_G2_EEPROM_CMD_RUNNING ; 
 int __bf_shf (int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g2_wait_bit (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_g2_eeprom_wait(struct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G2_EEPROM_CMD_BUSY);
	int err;

	err = mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_EEPROM_CMD, bit, 0);
	if (err)
		return err;

	bit = __bf_shf(MV88E6XXX_G2_EEPROM_CMD_RUNNING);

	return mv88e6xxx_g2_wait_bit(chip, MV88E6XXX_G2_EEPROM_CMD, bit, 0);
}