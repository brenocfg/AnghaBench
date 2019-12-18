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
struct veth_priv {int /*<<< orphan*/  peer; } ;
struct net_device {int ifindex; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device const*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int veth_get_iflink(const struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	struct net_device *peer;
	int iflink;

	rcu_read_lock();
	peer = rcu_dereference(priv->peer);
	iflink = peer ? peer->ifindex : 0;
	rcu_read_unlock();

	return iflink;
}