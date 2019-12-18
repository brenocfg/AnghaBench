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
struct mii_bus {char* name; int phy_mask; int /*<<< orphan*/ * parent; int /*<<< orphan*/  reset; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct bgmac* priv; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct bcma_device* core; } ;
struct bgmac {int phyaddr; TYPE_1__ bcma; } ;
struct bcma_device {int core_unit; int /*<<< orphan*/  dev; TYPE_2__* bus; } ;
struct TYPE_4__ {int num; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mii_bus* ERR_PTR (int) ; 
 int /*<<< orphan*/  bcma_mdio_mii_read ; 
 int /*<<< orphan*/  bcma_mdio_mii_write ; 
 int /*<<< orphan*/  bcma_mdio_phy_reset ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 

struct mii_bus *bcma_mdio_mii_register(struct bgmac *bgmac)
{
	struct bcma_device *core = bgmac->bcma.core;
	struct mii_bus *mii_bus;
	int err;

	mii_bus = mdiobus_alloc();
	if (!mii_bus) {
		err = -ENOMEM;
		goto err;
	}

	mii_bus->name = "bcma_mdio mii bus";
	sprintf(mii_bus->id, "%s-%d-%d", "bcma_mdio", core->bus->num,
		core->core_unit);
	mii_bus->priv = bgmac;
	mii_bus->read = bcma_mdio_mii_read;
	mii_bus->write = bcma_mdio_mii_write;
	mii_bus->reset = bcma_mdio_phy_reset;
	mii_bus->parent = &core->dev;
	mii_bus->phy_mask = ~(1 << bgmac->phyaddr);

	err = mdiobus_register(mii_bus);
	if (err) {
		dev_err(&core->dev, "Registration of mii bus failed\n");
		goto err_free_bus;
	}

	return mii_bus;

err_free_bus:
	mdiobus_free(mii_bus);
err:
	return ERR_PTR(err);
}