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
struct nixge_priv {struct mii_bus* mii_bus; int /*<<< orphan*/  dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct nixge_priv* priv; int /*<<< orphan*/  id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_mdio_read ; 
 int /*<<< orphan*/  nixge_mdio_write ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int nixge_mdio_setup(struct nixge_priv *priv, struct device_node *np)
{
	struct mii_bus *bus;

	bus = devm_mdiobus_alloc(priv->dev);
	if (!bus)
		return -ENOMEM;

	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(priv->dev));
	bus->priv = priv;
	bus->name = "nixge_mii_bus";
	bus->read = nixge_mdio_read;
	bus->write = nixge_mdio_write;
	bus->parent = priv->dev;

	priv->mii_bus = bus;

	return of_mdiobus_register(bus, np);
}