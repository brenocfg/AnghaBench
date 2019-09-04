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
struct net_device {int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
 int /*<<< orphan*/  NET_ADDR_STOLEN ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,struct net_device*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bond_set_dev_addr(struct net_device *bond_dev,
			      struct net_device *slave_dev)
{
	netdev_dbg(bond_dev, "bond_dev=%p slave_dev=%p slave_dev->name=%s slave_dev->addr_len=%d\n",
		   bond_dev, slave_dev, slave_dev->name, slave_dev->addr_len);
	memcpy(bond_dev->dev_addr, slave_dev->dev_addr, slave_dev->addr_len);
	bond_dev->addr_assign_type = NET_ADDR_STOLEN;
	call_netdevice_notifiers(NETDEV_CHANGEADDR, bond_dev);
}