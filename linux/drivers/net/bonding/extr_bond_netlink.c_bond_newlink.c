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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 int bond_changelink (struct net_device*,struct nlattr**,struct nlattr**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  bond_work_init_all (struct bonding*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int bond_newlink(struct net *src_net, struct net_device *bond_dev,
			struct nlattr *tb[], struct nlattr *data[],
			struct netlink_ext_ack *extack)
{
	int err;

	err = bond_changelink(bond_dev, tb, data, extack);
	if (err < 0)
		return err;

	err = register_netdevice(bond_dev);

	netif_carrier_off(bond_dev);
	if (!err) {
		struct bonding *bond = netdev_priv(bond_dev);

		bond_work_init_all(bond);
	}

	return err;
}