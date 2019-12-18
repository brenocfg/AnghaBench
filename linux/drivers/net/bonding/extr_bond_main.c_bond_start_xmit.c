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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bonding {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __bond_start_xmit (struct sk_buff*,struct net_device*) ; 
 scalar_t__ bond_has_slaves (struct bonding*) ; 
 int /*<<< orphan*/  bond_tx_drop (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  is_netpoll_tx_blocked (struct net_device*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bond_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bonding *bond = netdev_priv(dev);
	netdev_tx_t ret = NETDEV_TX_OK;

	/* If we risk deadlock from transmitting this in the
	 * netpoll path, tell netpoll to queue the frame for later tx
	 */
	if (unlikely(is_netpoll_tx_blocked(dev)))
		return NETDEV_TX_BUSY;

	rcu_read_lock();
	if (bond_has_slaves(bond))
		ret = __bond_start_xmit(skb, dev);
	else
		bond_tx_drop(dev, skb);
	rcu_read_unlock();

	return ret;
}