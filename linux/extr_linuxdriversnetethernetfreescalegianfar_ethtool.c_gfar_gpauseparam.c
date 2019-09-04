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
struct gfar_private {int /*<<< orphan*/  tx_pause_en; int /*<<< orphan*/  rx_pause_en; int /*<<< orphan*/  pause_aneg_en; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;

/* Variables and functions */
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gfar_gpauseparam(struct net_device *dev,
			     struct ethtool_pauseparam *epause)
{
	struct gfar_private *priv = netdev_priv(dev);

	epause->autoneg = !!priv->pause_aneg_en;
	epause->rx_pause = !!priv->rx_pause_en;
	epause->tx_pause = !!priv->tx_pause_en;
}