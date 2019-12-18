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
 unsigned int DLINK_EEPROM ; 
 short EE_CK ; 
 short EE_CS ; 
 int EE_DI ; 
 short EE_DO ; 
 short EE_EEP ; 
 int EE_READ_CMD ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  outb (short,unsigned int) ; 
 int /*<<< orphan*/  outb_p (short,unsigned int) ; 

__attribute__((used)) static int read_eeprom(unsigned int ioaddr, int location)
{
    int i, retval = 0;
    unsigned int ee_addr = ioaddr + DLINK_EEPROM;
    int read_cmd = location | (EE_READ_CMD << 8);

    outb(0, ee_addr);
    outb(EE_EEP|EE_CS, ee_addr);

    /* Shift the read command bits out. */
    for (i = 10; i >= 0; i--) {
	short dataval = (read_cmd & (1 << i)) ? EE_DO : 0;
	outb_p(EE_EEP|EE_CS|dataval, ee_addr);
	outb_p(EE_EEP|EE_CS|dataval|EE_CK, ee_addr);
    }
    outb(EE_EEP|EE_CS, ee_addr);

    for (i = 16; i > 0; i--) {
	outb_p(EE_EEP|EE_CS | EE_CK, ee_addr);
	retval = (retval << 1) | ((inb(ee_addr) & EE_DI) ? 1 : 0);
	outb_p(EE_EEP|EE_CS, ee_addr);
    }

    /* Terminate the EEPROM access. */
    outb(0, ee_addr);
    return retval;
}