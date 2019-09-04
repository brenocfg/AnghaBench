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
struct ssb_sprom {int boardflags_lo; } ;
struct ssb_device {int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct TYPE_4__ {int addr; } ;
struct phy_device {int supported; int advertising; TYPE_2__ mdio; } ;
struct mii_bus {char* name; int phy_mask; char* id; int /*<<< orphan*/  parent; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct b44* priv; } ;
struct b44 {int phy_addr; scalar_t__ old_link; int /*<<< orphan*/  dev; struct mii_bus* mii_bus; struct ssb_device* sdev; } ;
typedef  int /*<<< orphan*/  bus_id ;
struct TYPE_3__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 int B44_BOARDFLAG_ADM ; 
 int B44_BOARDFLAG_ROBO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  b44_adjust_link ; 
 int /*<<< orphan*/  b44_mdio_read_phylib ; 
 int /*<<< orphan*/  b44_mdio_write_phylib ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int instance ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_is_registered_device (struct mii_bus*,int) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int b44_register_phy_one(struct b44 *bp)
{
	struct mii_bus *mii_bus;
	struct ssb_device *sdev = bp->sdev;
	struct phy_device *phydev;
	char bus_id[MII_BUS_ID_SIZE + 3];
	struct ssb_sprom *sprom = &sdev->bus->sprom;
	int err;

	mii_bus = mdiobus_alloc();
	if (!mii_bus) {
		dev_err(sdev->dev, "mdiobus_alloc() failed\n");
		err = -ENOMEM;
		goto err_out;
	}

	mii_bus->priv = bp;
	mii_bus->read = b44_mdio_read_phylib;
	mii_bus->write = b44_mdio_write_phylib;
	mii_bus->name = "b44_eth_mii";
	mii_bus->parent = sdev->dev;
	mii_bus->phy_mask = ~(1 << bp->phy_addr);
	snprintf(mii_bus->id, MII_BUS_ID_SIZE, "%x", instance);

	bp->mii_bus = mii_bus;

	err = mdiobus_register(mii_bus);
	if (err) {
		dev_err(sdev->dev, "failed to register MII bus\n");
		goto err_out_mdiobus;
	}

	if (!mdiobus_is_registered_device(bp->mii_bus, bp->phy_addr) &&
	    (sprom->boardflags_lo & (B44_BOARDFLAG_ROBO | B44_BOARDFLAG_ADM))) {

		dev_info(sdev->dev,
			 "could not find PHY at %i, use fixed one\n",
			 bp->phy_addr);

		bp->phy_addr = 0;
		snprintf(bus_id, sizeof(bus_id), PHY_ID_FMT, "fixed-0",
			 bp->phy_addr);
	} else {
		snprintf(bus_id, sizeof(bus_id), PHY_ID_FMT, mii_bus->id,
			 bp->phy_addr);
	}

	phydev = phy_connect(bp->dev, bus_id, &b44_adjust_link,
			     PHY_INTERFACE_MODE_MII);
	if (IS_ERR(phydev)) {
		dev_err(sdev->dev, "could not attach PHY at %i\n",
			bp->phy_addr);
		err = PTR_ERR(phydev);
		goto err_out_mdiobus_unregister;
	}

	/* mask with MAC supported features */
	phydev->supported &= (SUPPORTED_100baseT_Half |
			      SUPPORTED_100baseT_Full |
			      SUPPORTED_Autoneg |
			      SUPPORTED_MII);
	phydev->advertising = phydev->supported;

	bp->old_link = 0;
	bp->phy_addr = phydev->mdio.addr;

	phy_attached_info(phydev);

	return 0;

err_out_mdiobus_unregister:
	mdiobus_unregister(mii_bus);

err_out_mdiobus:
	mdiobus_free(mii_bus);

err_out:
	return err;
}