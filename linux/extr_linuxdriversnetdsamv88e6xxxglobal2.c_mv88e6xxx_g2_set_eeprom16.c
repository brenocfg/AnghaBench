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
 int EROFS ; 
 int /*<<< orphan*/  MV88E6XXX_G2_EEPROM_CMD ; 
 int MV88E6XXX_G2_EEPROM_CMD_WRITE_EN ; 
 int mv88e6xxx_g2_eeprom_read16 (struct mv88e6xxx_chip*,unsigned int,int*) ; 
 int mv88e6xxx_g2_eeprom_write16 (struct mv88e6xxx_chip*,unsigned int,int) ; 
 int mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 

int mv88e6xxx_g2_set_eeprom16(struct mv88e6xxx_chip *chip,
			      struct ethtool_eeprom *eeprom, u8 *data)
{
	unsigned int offset = eeprom->offset;
	unsigned int len = eeprom->len;
	u16 val;
	int err;

	/* Ensure the RO WriteEn bit is set */
	err = mv88e6xxx_g2_read(chip, MV88E6XXX_G2_EEPROM_CMD, &val);
	if (err)
		return err;

	if (!(val & MV88E6XXX_G2_EEPROM_CMD_WRITE_EN))
		return -EROFS;

	eeprom->len = 0;

	if (offset & 1) {
		err = mv88e6xxx_g2_eeprom_read16(chip, offset >> 1, &val);
		if (err)
			return err;

		val = (*data++ << 8) | (val & 0xff);

		err = mv88e6xxx_g2_eeprom_write16(chip, offset >> 1, val);
		if (err)
			return err;

		offset++;
		len--;
		eeprom->len++;
	}

	while (len >= 2) {
		val = *data++;
		val |= *data++ << 8;

		err = mv88e6xxx_g2_eeprom_write16(chip, offset >> 1, val);
		if (err)
			return err;

		offset += 2;
		len -= 2;
		eeprom->len += 2;
	}

	if (len) {
		err = mv88e6xxx_g2_eeprom_read16(chip, offset >> 1, &val);
		if (err)
			return err;

		val = (val & 0xff00) | *data++;

		err = mv88e6xxx_g2_eeprom_write16(chip, offset >> 1, val);
		if (err)
			return err;

		offset++;
		len--;
		eeprom->len++;
	}

	return 0;
}