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
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectPage (int) ; 
 int /*<<< orphan*/  XIRCREG4_GPR1 ; 
 int /*<<< orphan*/  pr_debug (char*,struct net_device*) ; 

__attribute__((used)) static void
do_powerdown(struct net_device *dev)
{

    unsigned int ioaddr = dev->base_addr;

    pr_debug("do_powerdown(%p)\n", dev);

    SelectPage(4);
    PutByte(XIRCREG4_GPR1, 0);	     /* clear bit 0: power down */
    SelectPage(0);
}