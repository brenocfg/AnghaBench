#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {unsigned int base_addr; } ;
struct TYPE_2__ {scalar_t__ dmaing; scalar_t__ txing; } ;

/* Variables and functions */
 scalar_t__ AXNET_RESET ; 
 scalar_t__ E8390_CMD ; 
 int E8390_NODMA ; 
 int E8390_PAGE0 ; 
 int E8390_STOP ; 
 scalar_t__ EN0_ISR ; 
 int ENISR_RESET ; 
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void axnet_reset_8390(struct net_device *dev)
{
    unsigned int nic_base = dev->base_addr;
    int i;

    ei_status.txing = ei_status.dmaing = 0;

    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, nic_base + E8390_CMD);

    outb(inb(nic_base + AXNET_RESET), nic_base + AXNET_RESET);

    for (i = 0; i < 100; i++) {
	if ((inb_p(nic_base+EN0_ISR) & ENISR_RESET) != 0)
	    break;
	udelay(100);
    }
    outb_p(ENISR_RESET, nic_base + EN0_ISR); /* Ack intr. */
    
    if (i == 100)
	netdev_err(dev, "axnet_reset_8390() did not complete\n");
    
}