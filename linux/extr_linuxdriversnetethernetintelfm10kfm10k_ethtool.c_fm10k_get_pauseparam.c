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
struct fm10k_intfc {scalar_t__ rx_pause; } ;
struct ethtool_pauseparam {int tx_pause; int rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_get_pauseparam(struct net_device *dev,
				 struct ethtool_pauseparam *pause)
{
	struct fm10k_intfc *interface = netdev_priv(dev);

	/* record fixed values for autoneg and tx pause */
	pause->autoneg = 0;
	pause->tx_pause = 1;

	pause->rx_pause = interface->rx_pause ? 1 : 0;
}