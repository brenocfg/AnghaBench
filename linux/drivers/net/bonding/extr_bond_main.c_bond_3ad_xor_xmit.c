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
struct bonding {int /*<<< orphan*/  slave_arr; } ;
struct bond_up_slave {struct slave** arr; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_dev_queue_xmit (struct bonding*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_tx_drop (struct net_device*,struct sk_buff*) ; 
 unsigned int bond_xmit_hash (struct bonding*,struct sk_buff*) ; 
 scalar_t__ likely (unsigned int) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 struct bond_up_slave* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bond_3ad_xor_xmit(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct bonding *bond = netdev_priv(dev);
	struct slave *slave;
	struct bond_up_slave *slaves;
	unsigned int count;

	slaves = rcu_dereference(bond->slave_arr);
	count = slaves ? READ_ONCE(slaves->count) : 0;
	if (likely(count)) {
		slave = slaves->arr[bond_xmit_hash(bond, skb) % count];
		bond_dev_queue_xmit(bond, skb, slave->dev);
	} else {
		bond_tx_drop(dev, skb);
	}

	return NETDEV_TX_OK;
}