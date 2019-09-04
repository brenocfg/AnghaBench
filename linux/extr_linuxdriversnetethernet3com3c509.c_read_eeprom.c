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
typedef  int /*<<< orphan*/  ushort ;

/* Variables and functions */
 scalar_t__ EEPROM_READ ; 
 int /*<<< orphan*/  inw (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outw (scalar_t__,int) ; 

__attribute__((used)) static ushort read_eeprom(int ioaddr, int index)
{
	outw(EEPROM_READ + index, ioaddr + 10);
	/* Pause for at least 162 us. for the read to take place.
	   Some chips seem to require much longer */
	mdelay(2);
	return inw(ioaddr + 12);
}