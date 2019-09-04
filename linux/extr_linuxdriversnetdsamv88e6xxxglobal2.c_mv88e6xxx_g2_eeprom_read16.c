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
 int /*<<< orphan*/  MV88E6352_G2_EEPROM_DATA ; 
 int MV88E6XXX_G2_EEPROM_CMD_OP_READ ; 
 int mv88e6xxx_g2_eeprom_cmd (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_g2_eeprom_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mv88e6xxx_g2_eeprom_read16(struct mv88e6xxx_chip *chip,
				      u8 addr, u16 *data)
{
	u16 cmd = MV88E6XXX_G2_EEPROM_CMD_OP_READ | addr;
	int err;

	err = mv88e6xxx_g2_eeprom_wait(chip);
	if (err)
		return err;

	err = mv88e6xxx_g2_eeprom_cmd(chip, cmd);
	if (err)
		return err;

	return mv88e6xxx_g2_read(chip, MV88E6352_G2_EEPROM_DATA, data);
}