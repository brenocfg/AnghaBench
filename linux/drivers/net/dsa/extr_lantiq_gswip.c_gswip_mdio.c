#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gswip_priv {int /*<<< orphan*/  dev; struct dsa_switch* ds; } ;
struct dsa_switch {TYPE_1__* slave_mii_bus; int /*<<< orphan*/  phys_mii_mask; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  parent; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct gswip_priv* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_mdiobus_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_mdio_rd ; 
 int /*<<< orphan*/  gswip_mdio_wr ; 
 int of_mdiobus_register (TYPE_1__*,struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int gswip_mdio(struct gswip_priv *priv, struct device_node *mdio_np)
{
	struct dsa_switch *ds = priv->ds;

	ds->slave_mii_bus = devm_mdiobus_alloc(priv->dev);
	if (!ds->slave_mii_bus)
		return -ENOMEM;

	ds->slave_mii_bus->priv = priv;
	ds->slave_mii_bus->read = gswip_mdio_rd;
	ds->slave_mii_bus->write = gswip_mdio_wr;
	ds->slave_mii_bus->name = "lantiq,xrx200-mdio";
	snprintf(ds->slave_mii_bus->id, MII_BUS_ID_SIZE, "%s-mii",
		 dev_name(priv->dev));
	ds->slave_mii_bus->parent = priv->dev;
	ds->slave_mii_bus->phy_mask = ~ds->phys_mii_mask;

	return of_mdiobus_register(ds->slave_mii_bus, mdio_np);
}