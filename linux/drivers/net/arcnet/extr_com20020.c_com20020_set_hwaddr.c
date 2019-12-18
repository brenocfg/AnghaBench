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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int base_addr; int /*<<< orphan*/ * dev_addr; } ;
struct arcnet_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM20020_REG_W_XREG ; 
 int /*<<< orphan*/  SUB_NODE ; 
 int /*<<< orphan*/  arcnet_outb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  com20020_set_subaddress (struct arcnet_local*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int com20020_set_hwaddr(struct net_device *dev, void *addr)
{
	int ioaddr = dev->base_addr;
	struct arcnet_local *lp = netdev_priv(dev);
	struct sockaddr *hwaddr = addr;

	memcpy(dev->dev_addr, hwaddr->sa_data, 1);
	com20020_set_subaddress(lp, ioaddr, SUB_NODE);
	arcnet_outb(dev->dev_addr[0], ioaddr, COM20020_REG_W_XREG);

	return 0;
}