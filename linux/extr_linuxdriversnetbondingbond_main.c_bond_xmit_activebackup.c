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
struct slave {int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bonding {int /*<<< orphan*/  curr_active_slave; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  bond_dev_queue_xmit (struct bonding*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_tx_drop (struct net_device*,struct sk_buff*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 struct slave* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bond_xmit_activebackup(struct sk_buff *skb,
					  struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct slave *slave;

	slave = rcu_dereference(bond->curr_active_slave);
	if (slave)
		bond_dev_queue_xmit(bond, skb, slave->dev);
	else
		bond_tx_drop(bond_dev, skb);

	return NETDEV_TX_OK;
}