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
typedef  int u16 ;
struct netdev_private {scalar_t__ base; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 scalar_t__ StationAddr ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int __set_mac_addr(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	u16 addr16;

	addr16 = (dev->dev_addr[0] | (dev->dev_addr[1] << 8));
	iowrite16(addr16, np->base + StationAddr);
	addr16 = (dev->dev_addr[2] | (dev->dev_addr[3] << 8));
	iowrite16(addr16, np->base + StationAddr+2);
	addr16 = (dev->dev_addr[4] | (dev->dev_addr[5] << 8));
	iowrite16(addr16, np->base + StationAddr+4);
	return 0;
}