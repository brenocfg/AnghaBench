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
struct net_device {scalar_t__ addr_assign_type; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct bonding {int /*<<< orphan*/  bond_list; int /*<<< orphan*/  stats_lock_key; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  wq; } ;
struct bond_net {int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NET_ADDR_PERM ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_debug_register (struct bonding*) ; 
 int /*<<< orphan*/  bond_net_id ; 
 int /*<<< orphan*/  bond_prepare_sysfs_group (struct bonding*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_register_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bond_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bond_init(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct bond_net *bn = net_generic(dev_net(bond_dev), bond_net_id);

	netdev_dbg(bond_dev, "Begin bond_init\n");

	bond->wq = alloc_ordered_workqueue(bond_dev->name, WQ_MEM_RECLAIM);
	if (!bond->wq)
		return -ENOMEM;

	spin_lock_init(&bond->stats_lock);
	lockdep_register_key(&bond->stats_lock_key);
	lockdep_set_class(&bond->stats_lock, &bond->stats_lock_key);

	list_add_tail(&bond->bond_list, &bn->dev_list);

	bond_prepare_sysfs_group(bond);

	bond_debug_register(bond);

	/* Ensure valid dev_addr */
	if (is_zero_ether_addr(bond_dev->dev_addr) &&
	    bond_dev->addr_assign_type == NET_ADDR_PERM)
		eth_hw_addr_random(bond_dev);

	return 0;
}