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

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MCSR_NVCMD ; 
 unsigned char inb (scalar_t__) ; 

__attribute__((used)) static void apci3501_eeprom_wait(unsigned long iobase)
{
	unsigned char val;

	do {
		val = inb(iobase + AMCC_OP_REG_MCSR_NVCMD);
	} while (val & 0x80);
}