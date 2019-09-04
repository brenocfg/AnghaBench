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
struct net_device {int features; int flags; } ;
struct gfar_private {int /*<<< orphan*/  state; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFAR_RESETTING ; 
 int IFF_UP ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  gfar_mac_reset (struct gfar_private*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int startup_gfar (struct net_device*) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gfar_set_features(struct net_device *dev, netdev_features_t features)
{
	netdev_features_t changed = dev->features ^ features;
	struct gfar_private *priv = netdev_priv(dev);
	int err = 0;

	if (!(changed & (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			 NETIF_F_RXCSUM)))
		return 0;

	while (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	dev->features = features;

	if (dev->flags & IFF_UP) {
		/* Now we take down the rings to rebuild them */
		stop_gfar(dev);
		err = startup_gfar(dev);
	} else {
		gfar_mac_reset(priv);
	}

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	return err;
}