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
struct pch_phub_reg {int dummy; } ;

/* Variables and functions */
 int pch_phub_write_serial_rom (struct pch_phub_reg*,int,int) ; 

__attribute__((used)) static int pch_phub_gbe_serial_rom_conf(struct pch_phub_reg *chip)
{
	int retval;

	retval = pch_phub_write_serial_rom(chip, 0x0b, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x0a, 0x10);
	retval |= pch_phub_write_serial_rom(chip, 0x09, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x08, 0x02);

	retval |= pch_phub_write_serial_rom(chip, 0x0f, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x0e, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x0d, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x0c, 0x80);

	retval |= pch_phub_write_serial_rom(chip, 0x13, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x12, 0x10);
	retval |= pch_phub_write_serial_rom(chip, 0x11, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x10, 0x18);

	retval |= pch_phub_write_serial_rom(chip, 0x1b, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x1a, 0x10);
	retval |= pch_phub_write_serial_rom(chip, 0x19, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x18, 0x19);

	retval |= pch_phub_write_serial_rom(chip, 0x23, 0xbc);
	retval |= pch_phub_write_serial_rom(chip, 0x22, 0x10);
	retval |= pch_phub_write_serial_rom(chip, 0x21, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x20, 0x3a);

	retval |= pch_phub_write_serial_rom(chip, 0x27, 0x01);
	retval |= pch_phub_write_serial_rom(chip, 0x26, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x25, 0x00);
	retval |= pch_phub_write_serial_rom(chip, 0x24, 0x00);

	return retval;
}