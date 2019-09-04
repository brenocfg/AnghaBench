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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_eee {int /*<<< orphan*/  tx_lpi_timer; int /*<<< orphan*/  eee_enabled; } ;
struct bcmgenet_priv {struct ethtool_eee eee; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ GENET_IS_V1 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  UMAC_EEE_LPI_TIMER ; 
 int /*<<< orphan*/  bcmgenet_eee_enable_set (struct net_device*,int) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct bcmgenet_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int phy_ethtool_set_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 
 int phy_init_eee (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcmgenet_set_eee(struct net_device *dev, struct ethtool_eee *e)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct ethtool_eee *p = &priv->eee;
	int ret = 0;

	if (GENET_IS_V1(priv))
		return -EOPNOTSUPP;

	if (!dev->phydev)
		return -ENODEV;

	p->eee_enabled = e->eee_enabled;

	if (!p->eee_enabled) {
		bcmgenet_eee_enable_set(dev, false);
	} else {
		ret = phy_init_eee(dev->phydev, 0);
		if (ret) {
			netif_err(priv, hw, dev, "EEE initialization failed\n");
			return ret;
		}

		bcmgenet_umac_writel(priv, e->tx_lpi_timer, UMAC_EEE_LPI_TIMER);
		bcmgenet_eee_enable_set(dev, true);
	}

	return phy_ethtool_set_eee(dev->phydev, e);
}