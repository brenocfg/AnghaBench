#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {struct mii_bus* mii; TYPE_2__* plat; int /*<<< orphan*/  device; } ;
struct stmmac_mdio_bus_data {scalar_t__ probed_phy_irq; scalar_t__ irqs; int /*<<< orphan*/  phy_mask; scalar_t__ needs_reset; } ;
struct phy_device {scalar_t__ irq; } ;
struct TYPE_3__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct mii_bus {scalar_t__* irq; char* name; int /*<<< orphan*/  parent; int /*<<< orphan*/  phy_mask; struct net_device* priv; int /*<<< orphan*/  id; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int phy_addr; int bus_id; scalar_t__ phy_node; scalar_t__ has_xgmac; struct device_node* mdio_node; struct stmmac_mdio_bus_data* mdio_bus_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int MII_XGMAC_MAX_C22ADDR ; 
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 struct phy_device* mdiobus_get_phy (struct mii_bus*,int) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  stmmac_mdio_read ; 
 int /*<<< orphan*/  stmmac_mdio_reset ; 
 int /*<<< orphan*/  stmmac_mdio_write ; 
 int /*<<< orphan*/  stmmac_xgmac2_mdio_read ; 
 int /*<<< orphan*/  stmmac_xgmac2_mdio_write ; 

int stmmac_mdio_register(struct net_device *ndev)
{
	int err = 0;
	struct mii_bus *new_bus;
	struct stmmac_priv *priv = netdev_priv(ndev);
	struct stmmac_mdio_bus_data *mdio_bus_data = priv->plat->mdio_bus_data;
	struct device_node *mdio_node = priv->plat->mdio_node;
	struct device *dev = ndev->dev.parent;
	int addr, found, max_addr;

	if (!mdio_bus_data)
		return 0;

	new_bus = mdiobus_alloc();
	if (!new_bus)
		return -ENOMEM;

	if (mdio_bus_data->irqs)
		memcpy(new_bus->irq, mdio_bus_data->irqs, sizeof(new_bus->irq));

	new_bus->name = "stmmac";

	if (priv->plat->has_xgmac) {
		new_bus->read = &stmmac_xgmac2_mdio_read;
		new_bus->write = &stmmac_xgmac2_mdio_write;

		/* Right now only C22 phys are supported */
		max_addr = MII_XGMAC_MAX_C22ADDR + 1;

		/* Check if DT specified an unsupported phy addr */
		if (priv->plat->phy_addr > MII_XGMAC_MAX_C22ADDR)
			dev_err(dev, "Unsupported phy_addr (max=%d)\n",
					MII_XGMAC_MAX_C22ADDR);
	} else {
		new_bus->read = &stmmac_mdio_read;
		new_bus->write = &stmmac_mdio_write;
		max_addr = PHY_MAX_ADDR;
	}

	if (mdio_bus_data->needs_reset)
		new_bus->reset = &stmmac_mdio_reset;

	snprintf(new_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 new_bus->name, priv->plat->bus_id);
	new_bus->priv = ndev;
	new_bus->phy_mask = mdio_bus_data->phy_mask;
	new_bus->parent = priv->device;

	err = of_mdiobus_register(new_bus, mdio_node);
	if (err != 0) {
		dev_err(dev, "Cannot register the MDIO bus\n");
		goto bus_register_fail;
	}

	if (priv->plat->phy_node || mdio_node)
		goto bus_register_done;

	found = 0;
	for (addr = 0; addr < max_addr; addr++) {
		struct phy_device *phydev = mdiobus_get_phy(new_bus, addr);

		if (!phydev)
			continue;

		/*
		 * If an IRQ was provided to be assigned after
		 * the bus probe, do it here.
		 */
		if (!mdio_bus_data->irqs &&
		    (mdio_bus_data->probed_phy_irq > 0)) {
			new_bus->irq[addr] = mdio_bus_data->probed_phy_irq;
			phydev->irq = mdio_bus_data->probed_phy_irq;
		}

		/*
		 * If we're going to bind the MAC to this PHY bus,
		 * and no PHY number was provided to the MAC,
		 * use the one probed here.
		 */
		if (priv->plat->phy_addr == -1)
			priv->plat->phy_addr = addr;

		phy_attached_info(phydev);
		found = 1;
	}

	if (!found && !mdio_node) {
		dev_warn(dev, "No PHY found\n");
		mdiobus_unregister(new_bus);
		mdiobus_free(new_bus);
		return -ENODEV;
	}

bus_register_done:
	priv->mii = new_bus;

	return 0;

bus_register_fail:
	mdiobus_free(new_bus);
	return err;
}