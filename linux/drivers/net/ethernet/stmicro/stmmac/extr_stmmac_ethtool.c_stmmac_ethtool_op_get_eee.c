#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  eee; } ;
struct stmmac_priv {int /*<<< orphan*/  phylink; int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; TYPE_1__ dma_cap; } ;
struct net_device {int dummy; } ;
struct ethtool_eee {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_active; int /*<<< orphan*/  eee_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_get_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 

__attribute__((used)) static int stmmac_ethtool_op_get_eee(struct net_device *dev,
				     struct ethtool_eee *edata)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (!priv->dma_cap.eee)
		return -EOPNOTSUPP;

	edata->eee_enabled = priv->eee_enabled;
	edata->eee_active = priv->eee_active;
	edata->tx_lpi_timer = priv->tx_lpi_timer;

	return phylink_ethtool_get_eee(priv->phylink, edata);
}