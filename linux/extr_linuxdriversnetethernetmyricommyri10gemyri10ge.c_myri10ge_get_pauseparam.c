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
struct myri10ge_priv {int /*<<< orphan*/  pause; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
myri10ge_get_pauseparam(struct net_device *netdev,
			struct ethtool_pauseparam *pause)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	pause->autoneg = 0;
	pause->rx_pause = mgp->pause;
	pause->tx_pause = mgp->pause;
}