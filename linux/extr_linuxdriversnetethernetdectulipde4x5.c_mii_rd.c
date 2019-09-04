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
 int /*<<< orphan*/  MII_PREAMBLE ; 
 int /*<<< orphan*/  MII_STRD ; 
 int /*<<< orphan*/  mii_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_rdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_ta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_wdata (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mii_rd(u_char phyreg, u_char phyaddr, u_long ioaddr)
{
    mii_wdata(MII_PREAMBLE,  2, ioaddr);   /* Start of 34 bit preamble...    */
    mii_wdata(MII_PREAMBLE, 32, ioaddr);   /* ...continued                   */
    mii_wdata(MII_STRD, 4, ioaddr);        /* SFD and Read operation         */
    mii_address(phyaddr, ioaddr);          /* PHY address to be accessed     */
    mii_address(phyreg, ioaddr);           /* PHY Register to read           */
    mii_ta(MII_STRD, ioaddr);              /* Turn around time - 2 MDC       */

    return mii_rdata(ioaddr);              /* Read data                      */
}