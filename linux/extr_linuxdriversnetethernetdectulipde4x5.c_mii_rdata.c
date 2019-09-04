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
typedef  int s32 ;

/* Variables and functions */
 int MII_MRD ; 
 int MII_RD ; 
 int getfrom_mii (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mii_rdata(u_long ioaddr)
{
    int i;
    s32 tmp = 0;

    for (i=0; i<16; i++) {
	tmp <<= 1;
	tmp |= getfrom_mii(MII_MRD | MII_RD, ioaddr);
    }

    return tmp;
}