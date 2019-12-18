#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smsc911x_data {int idrev; TYPE_1__* mii_bus; scalar_t__ using_extphy; } ;
struct platform_device {char* name; int id; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int phy_mask; int /*<<< orphan*/ * parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct smsc911x_data* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  SMSC_MDIONAME ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw ; 
 TYPE_1__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 scalar_t__ mdiobus_register (TYPE_1__*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  smsc911x_mii_read ; 
 int /*<<< orphan*/  smsc911x_mii_write ; 
 int /*<<< orphan*/  smsc911x_phy_initialise_external (struct smsc911x_data*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int smsc911x_mii_init(struct platform_device *pdev,
			     struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	int err = -ENXIO;

	pdata->mii_bus = mdiobus_alloc();
	if (!pdata->mii_bus) {
		err = -ENOMEM;
		goto err_out_1;
	}

	pdata->mii_bus->name = SMSC_MDIONAME;
	snprintf(pdata->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, pdev->id);
	pdata->mii_bus->priv = pdata;
	pdata->mii_bus->read = smsc911x_mii_read;
	pdata->mii_bus->write = smsc911x_mii_write;

	pdata->mii_bus->parent = &pdev->dev;

	switch (pdata->idrev & 0xFFFF0000) {
	case 0x01170000:
	case 0x01150000:
	case 0x117A0000:
	case 0x115A0000:
		/* External PHY supported, try to autodetect */
		smsc911x_phy_initialise_external(pdata);
		break;
	default:
		SMSC_TRACE(pdata, hw, "External PHY is not supported, "
			   "using internal PHY");
		pdata->using_extphy = 0;
		break;
	}

	if (!pdata->using_extphy) {
		/* Mask all PHYs except ID 1 (internal) */
		pdata->mii_bus->phy_mask = ~(1 << 1);
	}

	if (mdiobus_register(pdata->mii_bus)) {
		SMSC_WARN(pdata, probe, "Error registering mii bus");
		goto err_out_free_bus_2;
	}

	return 0;

err_out_free_bus_2:
	mdiobus_free(pdata->mii_bus);
err_out_1:
	return err;
}