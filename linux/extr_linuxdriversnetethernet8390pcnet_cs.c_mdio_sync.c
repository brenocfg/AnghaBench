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
 int MDIO_DATA_WRITE1 ; 
 int MDIO_MASK ; 
 int MDIO_SHIFT_CLK ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 

__attribute__((used)) static void mdio_sync(unsigned int addr)
{
    int bits, mask = inb(addr) & MDIO_MASK;
    for (bits = 0; bits < 32; bits++) {
	outb(mask | MDIO_DATA_WRITE1, addr);
	outb(mask | MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, addr);
    }
}