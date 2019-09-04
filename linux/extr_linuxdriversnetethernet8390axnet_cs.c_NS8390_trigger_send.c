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
struct net_device {long base_addr; } ;
struct ei_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ E8390_CMD ; 
 int E8390_NODMA ; 
 int E8390_START ; 
 int E8390_TRANS ; 
 scalar_t__ EN0_TCNTHI ; 
 scalar_t__ EN0_TCNTLO ; 
 scalar_t__ EN0_TPSR ; 
 int inb_p (long) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static void NS8390_trigger_send(struct net_device *dev, unsigned int length,
								int start_page)
{
	long e8390_base = dev->base_addr;
 	struct ei_device *ei_local __attribute((unused)) = netdev_priv(dev);
    
	if (inb_p(e8390_base) & E8390_TRANS) 
	{
		netdev_warn(dev, "trigger_send() called with the transmitter busy\n");
		return;
	}
	outb_p(length & 0xff, e8390_base + EN0_TCNTLO);
	outb_p(length >> 8, e8390_base + EN0_TCNTHI);
	outb_p(start_page, e8390_base + EN0_TPSR);
	outb_p(E8390_NODMA+E8390_TRANS+E8390_START, e8390_base+E8390_CMD);
}