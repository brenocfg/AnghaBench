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
struct veth_priv {int requested_headroom; int /*<<< orphan*/  peer; } ;
struct net_device {int needed_headroom; } ;

/* Variables and functions */
 int max (int,int) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void veth_set_rx_headroom(struct net_device *dev, int new_hr)
{
	struct veth_priv *peer_priv, *priv = netdev_priv(dev);
	struct net_device *peer;

	if (new_hr < 0)
		new_hr = 0;

	rcu_read_lock();
	peer = rcu_dereference(priv->peer);
	if (unlikely(!peer))
		goto out;

	peer_priv = netdev_priv(peer);
	priv->requested_headroom = new_hr;
	new_hr = max(priv->requested_headroom, peer_priv->requested_headroom);
	dev->needed_headroom = new_hr;
	peer->needed_headroom = new_hr;

out:
	rcu_read_unlock();
}