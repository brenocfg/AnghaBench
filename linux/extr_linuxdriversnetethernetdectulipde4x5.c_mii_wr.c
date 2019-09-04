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
 int MII_PREAMBLE ; 
 int MII_STWR ; 
 int /*<<< orphan*/  mii_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_swap (int,int) ; 
 int /*<<< orphan*/  mii_ta (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_wdata (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mii_wr(int data, u_char phyreg, u_char phyaddr, u_long ioaddr)
{
    mii_wdata(MII_PREAMBLE,  2, ioaddr);   /* Start of 34 bit preamble...    */
    mii_wdata(MII_PREAMBLE, 32, ioaddr);   /* ...continued                   */
    mii_wdata(MII_STWR, 4, ioaddr);        /* SFD and Write operation        */
    mii_address(phyaddr, ioaddr);          /* PHY address to be accessed     */
    mii_address(phyreg, ioaddr);           /* PHY Register to write          */
    mii_ta(MII_STWR, ioaddr);              /* Turn around time - 2 MDC       */
    data = mii_swap(data, 16);             /* Swap data bit ordering         */
    mii_wdata(data, 16, ioaddr);           /* Write data                     */
}