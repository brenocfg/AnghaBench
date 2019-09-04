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
 int MV88E6XXX_G2_EEPROM_CMD_BUSY ; 
 int MV88E6XXX_G2_EEPROM_CMD_RUNNING ; 
 int mv88e6xxx_g2_wait (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_g2_eeprom_wait(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_g2_wait(chip, MV88E6XXX_G2_EEPROM_CMD,
				 MV88E6XXX_G2_EEPROM_CMD_BUSY |
				 MV88E6XXX_G2_EEPROM_CMD_RUNNING);
}