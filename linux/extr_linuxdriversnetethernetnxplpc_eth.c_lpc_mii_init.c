#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct netdata_local {TYPE_2__* mii_bus; int /*<<< orphan*/  ndev; TYPE_1__* pdev; int /*<<< orphan*/  net_base; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/ * parent; struct netdata_local* priv; int /*<<< orphan*/  id; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct TYPE_7__ {char* name; int id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int LPC_COMMAND_PASSRUNTFRAME ; 
 int LPC_COMMAND_RMII ; 
 int /*<<< orphan*/  LPC_ENET_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_SUPP (int /*<<< orphan*/ ) ; 
 int LPC_SUPP_RESET_RMII ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  lpc_mdio_read ; 
 int /*<<< orphan*/  lpc_mdio_reset ; 
 int /*<<< orphan*/  lpc_mdio_write ; 
 scalar_t__ lpc_mii_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ lpc_phy_interface_mode (int /*<<< orphan*/ *) ; 
 TYPE_2__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_2__*) ; 
 scalar_t__ mdiobus_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_mii_init(struct netdata_local *pldat)
{
	int err = -ENXIO;

	pldat->mii_bus = mdiobus_alloc();
	if (!pldat->mii_bus) {
		err = -ENOMEM;
		goto err_out;
	}

	/* Setup MII mode */
	if (lpc_phy_interface_mode(&pldat->pdev->dev) == PHY_INTERFACE_MODE_MII)
		writel(LPC_COMMAND_PASSRUNTFRAME,
		       LPC_ENET_COMMAND(pldat->net_base));
	else {
		writel((LPC_COMMAND_PASSRUNTFRAME | LPC_COMMAND_RMII),
		       LPC_ENET_COMMAND(pldat->net_base));
		writel(LPC_SUPP_RESET_RMII, LPC_ENET_SUPP(pldat->net_base));
	}

	pldat->mii_bus->name = "lpc_mii_bus";
	pldat->mii_bus->read = &lpc_mdio_read;
	pldat->mii_bus->write = &lpc_mdio_write;
	pldat->mii_bus->reset = &lpc_mdio_reset;
	snprintf(pldat->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pldat->pdev->name, pldat->pdev->id);
	pldat->mii_bus->priv = pldat;
	pldat->mii_bus->parent = &pldat->pdev->dev;

	platform_set_drvdata(pldat->pdev, pldat->mii_bus);

	if (mdiobus_register(pldat->mii_bus))
		goto err_out_unregister_bus;

	if (lpc_mii_probe(pldat->ndev) != 0)
		goto err_out_unregister_bus;

	return 0;

err_out_unregister_bus:
	mdiobus_unregister(pldat->mii_bus);
	mdiobus_free(pldat->mii_bus);
err_out:
	return err;
}