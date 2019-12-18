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
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; } ;
struct bcm_enet_priv {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;

/* Variables and functions */
 int bcm_enetsw_open (struct net_device*) ; 
 int /*<<< orphan*/  bcm_enetsw_stop (struct net_device*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bcm_enetsw_set_ringparam(struct net_device *dev,
				    struct ethtool_ringparam *ering)
{
	struct bcm_enet_priv *priv;
	int was_running;

	priv = netdev_priv(dev);

	was_running = 0;
	if (netif_running(dev)) {
		bcm_enetsw_stop(dev);
		was_running = 1;
	}

	priv->rx_ring_size = ering->rx_pending;
	priv->tx_ring_size = ering->tx_pending;

	if (was_running) {
		int err;

		err = bcm_enetsw_open(dev);
		if (err)
			dev_close(dev);
	}
	return 0;
}