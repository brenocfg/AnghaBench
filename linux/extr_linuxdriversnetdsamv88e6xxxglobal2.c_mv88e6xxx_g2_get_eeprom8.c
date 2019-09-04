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
typedef  int /*<<< orphan*/  u8 ;
struct mv88e6xxx_chip {int dummy; } ;
struct ethtool_eeprom {unsigned int offset; unsigned int len; } ;

/* Variables and functions */
 int mv88e6xxx_g2_eeprom_read8 (struct mv88e6xxx_chip*,unsigned int,int /*<<< orphan*/ *) ; 

int mv88e6xxx_g2_get_eeprom8(struct mv88e6xxx_chip *chip,
			     struct ethtool_eeprom *eeprom, u8 *data)
{
	unsigned int offset = eeprom->offset;
	unsigned int len = eeprom->len;
	int err;

	eeprom->len = 0;

	while (len) {
		err = mv88e6xxx_g2_eeprom_read8(chip, offset, data);
		if (err)
			return err;

		eeprom->len++;
		offset++;
		data++;
		len--;
	}

	return 0;
}