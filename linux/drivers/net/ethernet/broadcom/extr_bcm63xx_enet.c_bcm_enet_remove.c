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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bcm_enet_priv {int /*<<< orphan*/  mac_clk; int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  mii_bus; scalar_t__ has_phy; } ;
struct bcm63xx_enet_platform_data {int /*<<< orphan*/  (* mii_config ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_MIISC_REG ; 
 int /*<<< orphan*/  bcm_enet_mdio_read_mii ; 
 int /*<<< orphan*/  bcm_enet_mdio_write_mii ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct bcm63xx_enet_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int bcm_enet_remove(struct platform_device *pdev)
{
	struct bcm_enet_priv *priv;
	struct net_device *dev;

	/* stop netdevice */
	dev = platform_get_drvdata(pdev);
	priv = netdev_priv(dev);
	unregister_netdev(dev);

	/* turn off mdc clock */
	enet_writel(priv, 0, ENET_MIISC_REG);

	if (priv->has_phy) {
		mdiobus_unregister(priv->mii_bus);
		mdiobus_free(priv->mii_bus);
	} else {
		struct bcm63xx_enet_platform_data *pd;

		pd = dev_get_platdata(&pdev->dev);
		if (pd && pd->mii_config)
			pd->mii_config(dev, 0, bcm_enet_mdio_read_mii,
				       bcm_enet_mdio_write_mii);
	}

	/* disable hw block clocks */
	clk_disable_unprepare(priv->phy_clk);
	clk_disable_unprepare(priv->mac_clk);

	free_netdev(dev);
	return 0;
}