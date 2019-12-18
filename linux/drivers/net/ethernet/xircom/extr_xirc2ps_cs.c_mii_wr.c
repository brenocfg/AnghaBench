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
typedef  unsigned int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  SelectPage (int) ; 
 int /*<<< orphan*/  mii_idle (unsigned int) ; 
 int /*<<< orphan*/  mii_putbit (unsigned int,int) ; 
 int /*<<< orphan*/  mii_wbits (unsigned int,unsigned int,int) ; 

__attribute__((used)) static void
mii_wr(unsigned int ioaddr, u_char phyaddr, u_char phyreg, unsigned data,
       int len)
{
    int i;

    SelectPage(2);
    for (i=0; i < 32; i++)		/* 32 bit preamble */
	mii_putbit(ioaddr, 1);
    mii_wbits(ioaddr, 0x05, 4); 	/* Start and opcode for write */
    mii_wbits(ioaddr, phyaddr, 5);	/* PHY address to be accessed */
    mii_wbits(ioaddr, phyreg, 5);	/* PHY Register to write */
    mii_putbit(ioaddr, 1);		/* turn around */
    mii_putbit(ioaddr, 0);
    mii_wbits(ioaddr, data, len);	/* And write the data */
    mii_idle(ioaddr);
}