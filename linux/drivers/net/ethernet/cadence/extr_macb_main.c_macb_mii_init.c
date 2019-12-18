#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct macb {TYPE_2__* mii_bus; int /*<<< orphan*/  phy_node; TYPE_7__* dev; TYPE_1__* pdev; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {char* name; TYPE_9__* parent; struct macb* priv; int /*<<< orphan*/  id; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct TYPE_10__ {char* name; int id; TYPE_9__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MACB_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  MPE ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  macb_mdio_read ; 
 int /*<<< orphan*/  macb_mdio_write ; 
 int macb_mii_probe (TYPE_7__*) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_2__*) ; 
 int mdiobus_register (TYPE_2__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 int of_mdiobus_register (TYPE_2__*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int macb_mii_init(struct macb *bp)
{
	struct device_node *np;
	int err = -ENXIO;

	/* Enable management port */
	macb_writel(bp, NCR, MACB_BIT(MPE));

	bp->mii_bus = mdiobus_alloc();
	if (!bp->mii_bus) {
		err = -ENOMEM;
		goto err_out;
	}

	bp->mii_bus->name = "MACB_mii_bus";
	bp->mii_bus->read = &macb_mdio_read;
	bp->mii_bus->write = &macb_mdio_write;
	snprintf(bp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 bp->pdev->name, bp->pdev->id);
	bp->mii_bus->priv = bp;
	bp->mii_bus->parent = &bp->pdev->dev;

	dev_set_drvdata(&bp->dev->dev, bp->mii_bus);

	np = bp->pdev->dev.of_node;
	if (np && of_phy_is_fixed_link(np)) {
		if (of_phy_register_fixed_link(np) < 0) {
			dev_err(&bp->pdev->dev,
				"broken fixed-link specification %pOF\n", np);
			goto err_out_free_mdiobus;
		}

		err = mdiobus_register(bp->mii_bus);
	} else {
		err = of_mdiobus_register(bp->mii_bus, np);
	}

	if (err)
		goto err_out_free_fixed_link;

	err = macb_mii_probe(bp->dev);
	if (err)
		goto err_out_unregister_bus;

	return 0;

err_out_unregister_bus:
	mdiobus_unregister(bp->mii_bus);
err_out_free_fixed_link:
	if (np && of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
err_out_free_mdiobus:
	of_node_put(bp->phy_node);
	mdiobus_free(bp->mii_bus);
err_out:
	return err;
}