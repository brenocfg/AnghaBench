#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {char* name; int id; TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct ftgmac100 {TYPE_2__* mii_bus; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; scalar_t__ is_aspeed; scalar_t__ base; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/ * irq; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  priv; int /*<<< orphan*/  parent; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FTGMAC100_OFFSET_REVR ; 
 int /*<<< orphan*/  FTGMAC100_REVR_NEW_MDIO_INTERFACE ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PHY_INTERFACE_MODE_RGMII ; 
 int PHY_INTERFACE_MODE_RGMII_ID ; 
 int PHY_INTERFACE_MODE_RGMII_RXID ; 
 int PHY_INTERFACE_MODE_RGMII_TXID ; 
 int PHY_INTERFACE_MODE_RMII ; 
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ftgmac100_mdiobus_read ; 
 int /*<<< orphan*/  ftgmac100_mdiobus_write ; 
 int ftgmac100_mii_probe (struct ftgmac100*,int) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_2__*) ; 
 int mdiobus_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  phy_modes (int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftgmac100_setup_mdio(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	struct platform_device *pdev = to_platform_device(priv->dev);
	int phy_intf = PHY_INTERFACE_MODE_RGMII;
	struct device_node *np = pdev->dev.of_node;
	int i, err = 0;
	u32 reg;

	/* initialize mdio bus */
	priv->mii_bus = mdiobus_alloc();
	if (!priv->mii_bus)
		return -EIO;

	if (of_device_is_compatible(np, "aspeed,ast2400-mac") ||
	    of_device_is_compatible(np, "aspeed,ast2500-mac")) {
		/* The AST2600 has a separate MDIO controller */

		/* For the AST2400 and AST2500 this driver only supports the
		 * old MDIO interface
		 */
		reg = ioread32(priv->base + FTGMAC100_OFFSET_REVR);
		reg &= ~FTGMAC100_REVR_NEW_MDIO_INTERFACE;
		iowrite32(reg, priv->base + FTGMAC100_OFFSET_REVR);
	}

	/* Get PHY mode from device-tree */
	if (np) {
		/* Default to RGMII. It's a gigabit part after all */
		phy_intf = of_get_phy_mode(np);
		if (phy_intf < 0)
			phy_intf = PHY_INTERFACE_MODE_RGMII;

		/* Aspeed only supports these. I don't know about other IP
		 * block vendors so I'm going to just let them through for
		 * now. Note that this is only a warning if for some obscure
		 * reason the DT really means to lie about it or it's a newer
		 * part we don't know about.
		 *
		 * On the Aspeed SoC there are additionally straps and SCU
		 * control bits that could tell us what the interface is
		 * (or allow us to configure it while the IP block is held
		 * in reset). For now I chose to keep this driver away from
		 * those SoC specific bits and assume the device-tree is
		 * right and the SCU has been configured properly by pinmux
		 * or the firmware.
		 */
		if (priv->is_aspeed &&
		    phy_intf != PHY_INTERFACE_MODE_RMII &&
		    phy_intf != PHY_INTERFACE_MODE_RGMII &&
		    phy_intf != PHY_INTERFACE_MODE_RGMII_ID &&
		    phy_intf != PHY_INTERFACE_MODE_RGMII_RXID &&
		    phy_intf != PHY_INTERFACE_MODE_RGMII_TXID) {
			netdev_warn(netdev,
				   "Unsupported PHY mode %s !\n",
				   phy_modes(phy_intf));
		}
	}

	priv->mii_bus->name = "ftgmac100_mdio";
	snprintf(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%d",
		 pdev->name, pdev->id);
	priv->mii_bus->parent = priv->dev;
	priv->mii_bus->priv = priv->netdev;
	priv->mii_bus->read = ftgmac100_mdiobus_read;
	priv->mii_bus->write = ftgmac100_mdiobus_write;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		priv->mii_bus->irq[i] = PHY_POLL;

	err = mdiobus_register(priv->mii_bus);
	if (err) {
		dev_err(priv->dev, "Cannot register MDIO bus!\n");
		goto err_register_mdiobus;
	}

	err = ftgmac100_mii_probe(priv, phy_intf);
	if (err) {
		dev_err(priv->dev, "MII Probe failed!\n");
		goto err_mii_probe;
	}

	return 0;

err_mii_probe:
	mdiobus_unregister(priv->mii_bus);
err_register_mdiobus:
	mdiobus_free(priv->mii_bus);
	return err;
}