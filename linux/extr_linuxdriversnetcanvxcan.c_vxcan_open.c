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
struct vxcan_priv {int /*<<< orphan*/  peer; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int IFF_UP ; 
 struct vxcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxcan_open(struct net_device *dev)
{
	struct vxcan_priv *priv = netdev_priv(dev);
	struct net_device *peer = rtnl_dereference(priv->peer);

	if (!peer)
		return -ENOTCONN;

	if (peer->flags & IFF_UP) {
		netif_carrier_on(dev);
		netif_carrier_on(peer);
	}
	return 0;
}