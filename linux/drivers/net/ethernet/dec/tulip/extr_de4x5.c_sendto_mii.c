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
typedef  int u32 ;

/* Variables and functions */
 int MII_MDC ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
sendto_mii(u32 command, int data, u_long ioaddr)
{
    u32 j;

    j = (data & 1) << 17;
    outl(command | j, ioaddr);
    udelay(1);
    outl(command | MII_MDC | j, ioaddr);
    udelay(1);
}