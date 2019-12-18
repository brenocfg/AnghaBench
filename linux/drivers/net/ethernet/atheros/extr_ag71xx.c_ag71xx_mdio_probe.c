#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mii_bus {char* name; int /*<<< orphan*/  id; struct device* parent; struct ag71xx* priv; int /*<<< orphan*/  reset; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct device_node {char* name; } ;
struct device {struct device_node* of_node; } ;
struct ag71xx {int mac_idx; int /*<<< orphan*/  clk_mdio; struct mii_bus* mii_bus; int /*<<< orphan*/  mdio_reset; struct net_device* ndev; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_mdio_mii_read ; 
 int /*<<< orphan*/  ag71xx_mdio_mii_write ; 
 int /*<<< orphan*/  ag71xx_mdio_reset ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct mii_bus* devm_mdiobus_alloc (struct device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_err (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_reset_control_get_exclusive (struct device_node*,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int ag71xx_mdio_probe(struct ag71xx *ag)
{
	struct device *dev = &ag->pdev->dev;
	struct net_device *ndev = ag->ndev;
	static struct mii_bus *mii_bus;
	struct device_node *np, *mnp;
	int err;

	np = dev->of_node;
	ag->mii_bus = NULL;

	ag->clk_mdio = devm_clk_get(dev, "mdio");
	if (IS_ERR(ag->clk_mdio)) {
		netif_err(ag, probe, ndev, "Failed to get mdio clk.\n");
		return PTR_ERR(ag->clk_mdio);
	}

	err = clk_prepare_enable(ag->clk_mdio);
	if (err) {
		netif_err(ag, probe, ndev, "Failed to enable mdio clk.\n");
		return err;
	}

	mii_bus = devm_mdiobus_alloc(dev);
	if (!mii_bus) {
		err = -ENOMEM;
		goto mdio_err_put_clk;
	}

	ag->mdio_reset = of_reset_control_get_exclusive(np, "mdio");
	if (IS_ERR(ag->mdio_reset)) {
		netif_err(ag, probe, ndev, "Failed to get reset mdio.\n");
		return PTR_ERR(ag->mdio_reset);
	}

	mii_bus->name = "ag71xx_mdio";
	mii_bus->read = ag71xx_mdio_mii_read;
	mii_bus->write = ag71xx_mdio_mii_write;
	mii_bus->reset = ag71xx_mdio_reset;
	mii_bus->priv = ag;
	mii_bus->parent = dev;
	snprintf(mii_bus->id, MII_BUS_ID_SIZE, "%s.%d", np->name, ag->mac_idx);

	if (!IS_ERR(ag->mdio_reset)) {
		reset_control_assert(ag->mdio_reset);
		msleep(100);
		reset_control_deassert(ag->mdio_reset);
		msleep(200);
	}

	mnp = of_get_child_by_name(np, "mdio");
	err = of_mdiobus_register(mii_bus, mnp);
	of_node_put(mnp);
	if (err)
		goto mdio_err_put_clk;

	ag->mii_bus = mii_bus;

	return 0;

mdio_err_put_clk:
	clk_disable_unprepare(ag->clk_mdio);
	return err;
}