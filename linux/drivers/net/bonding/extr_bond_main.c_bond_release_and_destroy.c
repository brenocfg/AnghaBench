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
struct net_device {int /*<<< orphan*/  priv_flags; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DISABLE_NETPOLL ; 
 int __bond_release_one (struct net_device*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  bond_has_slaves (struct bonding*) ; 
 int /*<<< orphan*/  bond_remove_proc_entry (struct bonding*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int bond_release_and_destroy(struct net_device *bond_dev,
				    struct net_device *slave_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	int ret;

	ret = __bond_release_one(bond_dev, slave_dev, false, true);
	if (ret == 0 && !bond_has_slaves(bond)) {
		bond_dev->priv_flags |= IFF_DISABLE_NETPOLL;
		netdev_info(bond_dev, "Destroying bond\n");
		bond_remove_proc_entry(bond);
		unregister_netdevice(bond_dev);
	}
	return ret;
}