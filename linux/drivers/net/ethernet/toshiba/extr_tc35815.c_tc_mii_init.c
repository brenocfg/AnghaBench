#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tc35815_local {TYPE_3__* mii_bus; TYPE_2__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/ * parent; struct net_device* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_8__ {int devfn; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_7__ {int number; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 TYPE_3__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_3__*) ; 
 int mdiobus_register (TYPE_3__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_3__*) ; 
 struct tc35815_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tc_mdio_read ; 
 int /*<<< orphan*/  tc_mdio_write ; 
 int tc_mii_probe (struct net_device*) ; 

__attribute__((used)) static int tc_mii_init(struct net_device *dev)
{
	struct tc35815_local *lp = netdev_priv(dev);
	int err;

	lp->mii_bus = mdiobus_alloc();
	if (lp->mii_bus == NULL) {
		err = -ENOMEM;
		goto err_out;
	}

	lp->mii_bus->name = "tc35815_mii_bus";
	lp->mii_bus->read = tc_mdio_read;
	lp->mii_bus->write = tc_mdio_write;
	snprintf(lp->mii_bus->id, MII_BUS_ID_SIZE, "%x",
		 (lp->pci_dev->bus->number << 8) | lp->pci_dev->devfn);
	lp->mii_bus->priv = dev;
	lp->mii_bus->parent = &lp->pci_dev->dev;
	err = mdiobus_register(lp->mii_bus);
	if (err)
		goto err_out_free_mii_bus;
	err = tc_mii_probe(dev);
	if (err)
		goto err_out_unregister_bus;
	return 0;

err_out_unregister_bus:
	mdiobus_unregister(lp->mii_bus);
err_out_free_mii_bus:
	mdiobus_free(lp->mii_bus);
err_out:
	return err;
}