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
struct phy_device {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_wolinfo {scalar_t__ wolopts; int /*<<< orphan*/  supported; int /*<<< orphan*/  cmd; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct ave_private {int nclks; int nrsts; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * rst; int /*<<< orphan*/  mdio; struct phy_device* phydev; int /*<<< orphan*/  pinmode_val; int /*<<< orphan*/  pinmode_mask; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETHTOOL_GWOL ; 
 int /*<<< orphan*/  SG_ETPINMODE ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  ave_ethtool_get_wol (struct net_device*,struct ethtool_wolinfo*) ; 
 int /*<<< orphan*/  ave_ethtool_set_wol (struct net_device*,struct ethtool_wolinfo*) ; 
 int /*<<< orphan*/  ave_global_reset (struct net_device*) ; 
 int /*<<< orphan*/  ave_phy_adjust_link ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_mdiobus_register (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct phy_device* of_phy_get_and_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  phy_interface_is_rgmii (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ave_init(struct net_device *ndev)
{
	struct ethtool_wolinfo wol = { .cmd = ETHTOOL_GWOL };
	struct ave_private *priv = netdev_priv(ndev);
	struct device *dev = ndev->dev.parent;
	struct device_node *np = dev->of_node;
	struct device_node *mdio_np;
	struct phy_device *phydev;
	int nc, nr, ret;

	/* enable clk because of hw access until ndo_open */
	for (nc = 0; nc < priv->nclks; nc++) {
		ret = clk_prepare_enable(priv->clk[nc]);
		if (ret) {
			dev_err(dev, "can't enable clock\n");
			goto out_clk_disable;
		}
	}

	for (nr = 0; nr < priv->nrsts; nr++) {
		ret = reset_control_deassert(priv->rst[nr]);
		if (ret) {
			dev_err(dev, "can't deassert reset\n");
			goto out_reset_assert;
		}
	}

	ret = regmap_update_bits(priv->regmap, SG_ETPINMODE,
				 priv->pinmode_mask, priv->pinmode_val);
	if (ret)
		return ret;

	ave_global_reset(ndev);

	mdio_np = of_get_child_by_name(np, "mdio");
	if (!mdio_np) {
		dev_err(dev, "mdio node not found\n");
		ret = -EINVAL;
		goto out_reset_assert;
	}
	ret = of_mdiobus_register(priv->mdio, mdio_np);
	of_node_put(mdio_np);
	if (ret) {
		dev_err(dev, "failed to register mdiobus\n");
		goto out_reset_assert;
	}

	phydev = of_phy_get_and_connect(ndev, np, ave_phy_adjust_link);
	if (!phydev) {
		dev_err(dev, "could not attach to PHY\n");
		ret = -ENODEV;
		goto out_mdio_unregister;
	}

	priv->phydev = phydev;

	ave_ethtool_get_wol(ndev, &wol);
	device_set_wakeup_capable(&ndev->dev, !!wol.supported);

	/* set wol initial state disabled */
	wol.wolopts = 0;
	ave_ethtool_set_wol(ndev, &wol);

	if (!phy_interface_is_rgmii(phydev))
		phy_set_max_speed(phydev, SPEED_100);

	phy_support_asym_pause(phydev);

	phy_attached_info(phydev);

	return 0;

out_mdio_unregister:
	mdiobus_unregister(priv->mdio);
out_reset_assert:
	while (--nr >= 0)
		reset_control_assert(priv->rst[nr]);
out_clk_disable:
	while (--nc >= 0)
		clk_disable_unprepare(priv->clk[nc]);

	return ret;
}