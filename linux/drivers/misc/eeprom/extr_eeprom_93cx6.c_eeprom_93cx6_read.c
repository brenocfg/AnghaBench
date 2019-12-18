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
struct eeprom_93cx6 {int const width; } ;

/* Variables and functions */
 int const PCI_EEPROM_READ_OPCODE ; 
 scalar_t__ PCI_EEPROM_WIDTH_OPCODE ; 
 int /*<<< orphan*/  eeprom_93cx6_cleanup (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  eeprom_93cx6_read_bits (struct eeprom_93cx6*,int*,int) ; 
 int /*<<< orphan*/  eeprom_93cx6_startup (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  eeprom_93cx6_write_bits (struct eeprom_93cx6*,int,scalar_t__) ; 

void eeprom_93cx6_read(struct eeprom_93cx6 *eeprom, const u8 word,
	u16 *data)
{
	u16 command;

	/*
	 * Initialize the eeprom register
	 */
	eeprom_93cx6_startup(eeprom);

	/*
	 * Select the read opcode and the word to be read.
	 */
	command = (PCI_EEPROM_READ_OPCODE << eeprom->width) | word;
	eeprom_93cx6_write_bits(eeprom, command,
		PCI_EEPROM_WIDTH_OPCODE + eeprom->width);

	/*
	 * Read the requested 16 bits.
	 */
	eeprom_93cx6_read_bits(eeprom, data, 16);

	/*
	 * Cleanup eeprom register.
	 */
	eeprom_93cx6_cleanup(eeprom);
}