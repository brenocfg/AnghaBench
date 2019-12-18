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
struct net_device {int dummy; } ;
struct ltq_etop_priv {TYPE_2__* mii_bus; TYPE_1__* pdev; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct net_device* priv; } ;
struct TYPE_6__ {char* name; int id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ ltq_etop_mdio_probe (struct net_device*) ; 
 int /*<<< orphan*/  ltq_etop_mdio_rd ; 
 int /*<<< orphan*/  ltq_etop_mdio_wr ; 
 TYPE_2__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_2__*) ; 
 scalar_t__ mdiobus_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
ltq_etop_mdio_init(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	int err;

	priv->mii_bus = mdiobus_alloc();
	if (!priv->mii_bus) {
		netdev_err(dev, "failed to allocate mii bus\n");
		err = -ENOMEM;
		goto err_out;
	}

	priv->mii_bus->priv = dev;
	priv->mii_bus->read = ltq_etop_mdio_rd;
	priv->mii_bus->write = ltq_etop_mdio_wr;
	priv->mii_bus->name = "ltq_mii";
	snprintf(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		priv->pdev->name, priv->pdev->id);
	if (mdiobus_register(priv->mii_bus)) {
		err = -ENXIO;
		goto err_out_free_mdiobus;
	}

	if (ltq_etop_mdio_probe(dev)) {
		err = -ENXIO;
		goto err_out_unregister_bus;
	}
	return 0;

err_out_unregister_bus:
	mdiobus_unregister(priv->mii_bus);
err_out_free_mdiobus:
	mdiobus_free(priv->mii_bus);
err_out:
	return err;
}