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
struct stmmac_priv {int /*<<< orphan*/  rx_riwt; int /*<<< orphan*/  rx_coal_frames; scalar_t__ use_riwt; int /*<<< orphan*/  tx_coal_frames; int /*<<< orphan*/  tx_coal_timer; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_riwt2usec (int /*<<< orphan*/ ,struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_get_coalesce(struct net_device *dev,
			       struct ethtool_coalesce *ec)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	ec->tx_coalesce_usecs = priv->tx_coal_timer;
	ec->tx_max_coalesced_frames = priv->tx_coal_frames;

	if (priv->use_riwt) {
		ec->rx_max_coalesced_frames = priv->rx_coal_frames;
		ec->rx_coalesce_usecs = stmmac_riwt2usec(priv->rx_riwt, priv);
	}

	return 0;
}