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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int MII_MRD ; 
 int MII_MWR ; 
 int MII_RD ; 
 scalar_t__ MII_STWR ; 
 int MII_WR ; 
 int /*<<< orphan*/  getfrom_mii (int,scalar_t__) ; 
 int /*<<< orphan*/  sendto_mii (int,int,scalar_t__) ; 

__attribute__((used)) static void
mii_ta(u_long rw, u_long ioaddr)
{
    if (rw == MII_STWR) {
	sendto_mii(MII_MWR | MII_WR, 1, ioaddr);
	sendto_mii(MII_MWR | MII_WR, 0, ioaddr);
    } else {
	getfrom_mii(MII_MRD | MII_RD, ioaddr);        /* Tri-state MDIO */
    }
}