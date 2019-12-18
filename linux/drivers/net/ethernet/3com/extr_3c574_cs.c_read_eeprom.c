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
 scalar_t__ EEPROM_Read ; 
 scalar_t__ Wn0EepromCmd ; 
 scalar_t__ Wn0EepromData ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static unsigned short read_eeprom(unsigned int ioaddr, int index)
{
	int timer;
	outw(EEPROM_Read + index, ioaddr + Wn0EepromCmd);
	/* Pause for at least 162 usec for the read to take place. */
	for (timer = 1620; timer >= 0; timer--) {
		if ((inw(ioaddr + Wn0EepromCmd) & 0x8000) == 0)
			break;
	}
	return inw(ioaddr + Wn0EepromData);
}