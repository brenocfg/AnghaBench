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
struct net_device {long base_addr; int flags; } ;
struct ei_device {int* mcfilter; } ;

/* Variables and functions */
 scalar_t__ E8390_CMD ; 
 int E8390_NODMA ; 
 int E8390_PAGE0 ; 
 int E8390_PAGE1 ; 
 int E8390_RXCONFIG ; 
 int E8390_START ; 
 scalar_t__ EN0_RXCR ; 
 scalar_t__ EN1_MULT_SHIFT (int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  make_mc_bits (int*,struct net_device*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static void do_set_multicast_list(struct net_device *dev)
{
	long e8390_base = dev->base_addr;
	int i;
	struct ei_device *ei_local = netdev_priv(dev);

	if (!(dev->flags&(IFF_PROMISC|IFF_ALLMULTI))) {
		memset(ei_local->mcfilter, 0, 8);
		if (!netdev_mc_empty(dev))
			make_mc_bits(ei_local->mcfilter, dev);
	} else {
		/* set to accept-all */
		memset(ei_local->mcfilter, 0xFF, 8);
	}

	outb_p(E8390_NODMA + E8390_PAGE1, e8390_base + E8390_CMD);
	for(i = 0; i < 8; i++) 
	{
		outb_p(ei_local->mcfilter[i], e8390_base + EN1_MULT_SHIFT(i));
	}
	outb_p(E8390_NODMA + E8390_PAGE0, e8390_base + E8390_CMD);

  	if(dev->flags&IFF_PROMISC)
  		outb_p(E8390_RXCONFIG | 0x58, e8390_base + EN0_RXCR);
	else if (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev))
  		outb_p(E8390_RXCONFIG | 0x48, e8390_base + EN0_RXCR);
  	else
  		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR);

	outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
}