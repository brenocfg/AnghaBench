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
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;
struct ethtool_eeprom {unsigned int offset; unsigned int len; } ;

/* Variables and functions */
 int mv88e6xxx_g2_eeprom_read16 (struct mv88e6xxx_chip*,unsigned int,int*) ; 

int mv88e6xxx_g2_get_eeprom16(struct mv88e6xxx_chip *chip,
			      struct ethtool_eeprom *eeprom, u8 *data)
{
	unsigned int offset = eeprom->offset;
	unsigned int len = eeprom->len;
	u16 val;
	int err;

	eeprom->len = 0;

	if (offset & 1) {
		err = mv88e6xxx_g2_eeprom_read16(chip, offset >> 1, &val);
		if (err)
			return err;

		*data++ = (val >> 8) & 0xff;

		offset++;
		len--;
		eeprom->len++;
	}

	while (len >= 2) {
		err = mv88e6xxx_g2_eeprom_read16(chip, offset >> 1, &val);
		if (err)
			return err;

		*data++ = val & 0xff;
		*data++ = (val >> 8) & 0xff;

		offset += 2;
		len -= 2;
		eeprom->len += 2;
	}

	if (len) {
		err = mv88e6xxx_g2_eeprom_read16(chip, offset >> 1, &val);
		if (err)
			return err;

		*data++ = val & 0xff;

		offset++;
		len--;
		eeprom->len++;
	}

	return 0;
}