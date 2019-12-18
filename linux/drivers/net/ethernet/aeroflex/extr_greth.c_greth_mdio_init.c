#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  dev; } ;
struct greth_private {int irq; TYPE_1__* mdio; struct net_device* netdev; scalar_t__ edcl; } ;
struct TYPE_5__ {char* name; struct greth_private* priv; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int greth_edcl ; 
 int /*<<< orphan*/  greth_link_change (struct net_device*) ; 
 int greth_mdio_probe (struct net_device*) ; 
 int /*<<< orphan*/  greth_mdio_read ; 
 int /*<<< orphan*/  greth_mdio_write ; 
 int jiffies ; 
 TYPE_1__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int mdiobus_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 scalar_t__ netif_msg_probe (struct greth_private*) ; 
 int /*<<< orphan*/  phy_aneg_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_read_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_aneg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int greth_mdio_init(struct greth_private *greth)
{
	int ret;
	unsigned long timeout;
	struct net_device *ndev = greth->netdev;

	greth->mdio = mdiobus_alloc();
	if (!greth->mdio) {
		return -ENOMEM;
	}

	greth->mdio->name = "greth-mdio";
	snprintf(greth->mdio->id, MII_BUS_ID_SIZE, "%s-%d", greth->mdio->name, greth->irq);
	greth->mdio->read = greth_mdio_read;
	greth->mdio->write = greth_mdio_write;
	greth->mdio->priv = greth;

	ret = mdiobus_register(greth->mdio);
	if (ret) {
		goto error;
	}

	ret = greth_mdio_probe(greth->netdev);
	if (ret) {
		if (netif_msg_probe(greth))
			dev_err(&greth->netdev->dev, "failed to probe MDIO bus\n");
		goto unreg_mdio;
	}

	phy_start(ndev->phydev);

	/* If Ethernet debug link is used make autoneg happen right away */
	if (greth->edcl && greth_edcl == 1) {
		phy_start_aneg(ndev->phydev);
		timeout = jiffies + 6*HZ;
		while (!phy_aneg_done(ndev->phydev) &&
		       time_before(jiffies, timeout)) {
		}
		phy_read_status(ndev->phydev);
		greth_link_change(greth->netdev);
	}

	return 0;

unreg_mdio:
	mdiobus_unregister(greth->mdio);
error:
	mdiobus_free(greth->mdio);
	return ret;
}