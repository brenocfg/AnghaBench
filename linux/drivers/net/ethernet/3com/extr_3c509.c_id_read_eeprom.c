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
typedef  int ushort ;

/* Variables and functions */
 scalar_t__ EEPROM_READ ; 
 int el3_debug ; 
 int /*<<< orphan*/  id_port ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static ushort id_read_eeprom(int index)
{
	int bit, word = 0;

	/* Issue read command, and pause for at least 162 us. for it to complete.
	   Assume extra-fast 16Mhz bus. */
	outb(EEPROM_READ + index, id_port);

	/* Pause for at least 162 us. for the read to take place. */
	/* Some chips seem to require much longer */
	mdelay(4);

	for (bit = 15; bit >= 0; bit--)
		word = (word << 1) + (inb(id_port) & 0x01);

	if (el3_debug > 3)
		pr_debug("  3c509 EEPROM word %d %#4.4x.\n", index, word);

	return word;
}