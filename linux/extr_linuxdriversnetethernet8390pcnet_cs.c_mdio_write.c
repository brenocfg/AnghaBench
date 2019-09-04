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
typedef  int u_int ;

/* Variables and functions */
 int MDIO_DATA_WRITE0 ; 
 int MDIO_DATA_WRITE1 ; 
 int MDIO_MASK ; 
 int MDIO_SHIFT_CLK ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  mdio_sync (unsigned int) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 

__attribute__((used)) static void mdio_write(unsigned int addr, int phy_id, int loc, int value)
{
    u_int cmd = (0x05<<28)|(phy_id<<23)|(loc<<18)|(1<<17)|value;
    int i, mask = inb(addr) & MDIO_MASK;

    mdio_sync(addr);
    for (i = 31; i >= 0; i--) {
	int dat = (cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
	outb(mask | dat, addr);
	outb(mask | dat | MDIO_SHIFT_CLK, addr);
    }
    for (i = 1; i >= 0; i--) {
	outb(mask, addr);
	outb(mask | MDIO_SHIFT_CLK, addr);
    }
}