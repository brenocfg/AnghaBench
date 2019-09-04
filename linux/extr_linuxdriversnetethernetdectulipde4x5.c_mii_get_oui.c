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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ID0 ; 
 int /*<<< orphan*/  MII_ID1 ; 
 int mii_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mii_get_oui(u_char phyaddr, u_long ioaddr)
{
/*
    union {
	u_short reg;
	u_char breg[2];
    } a;
    int i, r2, r3, ret=0;*/
    int r2, r3;

    /* Read r2 and r3 */
    r2 = mii_rd(MII_ID0, phyaddr, ioaddr);
    r3 = mii_rd(MII_ID1, phyaddr, ioaddr);
                                                /* SEEQ and Cypress way * /
    / * Shuffle r2 and r3 * /
    a.reg=0;
    r3 = ((r3>>10)|(r2<<6))&0x0ff;
    r2 = ((r2>>2)&0x3fff);

    / * Bit reverse r3 * /
    for (i=0;i<8;i++) {
	ret<<=1;
	ret |= (r3&1);
	r3>>=1;
    }

    / * Bit reverse r2 * /
    for (i=0;i<16;i++) {
	a.reg<<=1;
	a.reg |= (r2&1);
	r2>>=1;
    }

    / * Swap r2 bytes * /
    i=a.breg[0];
    a.breg[0]=a.breg[1];
    a.breg[1]=i;

    return (a.reg<<8)|ret; */                 /* SEEQ and Cypress way */
/*    return (r2<<6)|(u_int)(r3>>10); */      /* NATIONAL and BROADCOM way */
    return r2;                                  /* (I did it) My way */
}