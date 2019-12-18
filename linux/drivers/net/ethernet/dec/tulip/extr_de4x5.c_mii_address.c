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
typedef  int u_char ;

/* Variables and functions */
 int MII_MWR ; 
 int MII_WR ; 
 int mii_swap (int,int) ; 
 int /*<<< orphan*/  sendto_mii (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mii_address(u_char addr, u_long ioaddr)
{
    int i;

    addr = mii_swap(addr, 5);
    for (i=0; i<5; i++) {
	sendto_mii(MII_MWR | MII_WR, addr, ioaddr);
	addr >>= 1;
    }
}