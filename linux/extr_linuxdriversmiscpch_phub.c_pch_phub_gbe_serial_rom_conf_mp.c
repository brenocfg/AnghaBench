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
typedef  int u32 ;
struct pch_phub_reg {int dummy; } ;

/* Variables and functions */
 int pch_phub_write_serial_rom (struct pch_phub_reg*,int,int) ; 

__attribute__((used)) static int pch_phub_gbe_serial_rom_conf_mp(struct pch_phub_reg *chip)
{
	int retval;
	u32 offset_addr;

	offset_addr = 0x200;
	retval = pch_phub_write_serial_rom(chip, 0x03 + offset_addr, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x02 + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x01 + offset_addr, 0x40);
	retval |= pch_phub_write_serial_rom(chip, 0x00 + offset_addr, 0x02);

	retval |= pch_phub_write_serial_rom(chip, 0x07 + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x06 + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x05 + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x04 + offset_addr, 0x80);

	retval |= pch_phub_write_serial_rom(chip, 0x0b + offset_addr, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x0a + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x09 + offset_addr, 0x40);
	retval |= pch_phub_write_serial_rom(chip, 0x08 + offset_addr, 0x18);

	retval |= pch_phub_write_serial_rom(chip, 0x13 + offset_addr, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x12 + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x11 + offset_addr, 0x40);
	retval |= pch_phub_write_serial_rom(chip, 0x10 + offset_addr, 0x19);

	retval |= pch_phub_write_serial_rom(chip, 0x1b + offset_addr, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x1a + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x19 + offset_addr, 0x40);
	retval |= pch_phub_write_serial_rom(chip, 0x18 + offset_addr, 0x3a);

	retval |= pch_phub_write_serial_rom(chip, 0x1f + offset_addr, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x1e + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x1d + offset_addr, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x1c + offset_addr, 0x00);

	return retval;
}