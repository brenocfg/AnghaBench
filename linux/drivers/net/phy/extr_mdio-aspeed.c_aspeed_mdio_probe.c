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
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct mii_bus {int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/  name; struct aspeed_mdio* priv; } ;
struct aspeed_mdio {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_mdio_read ; 
 int /*<<< orphan*/  aspeed_mdio_write ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct mii_bus* devm_mdiobus_alloc_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_mdio_probe(struct platform_device *pdev)
{
	struct aspeed_mdio *ctx;
	struct mii_bus *bus;
	int rc;

	bus = devm_mdiobus_alloc_size(&pdev->dev, sizeof(*ctx));
	if (!bus)
		return -ENOMEM;

	ctx = bus->priv;
	ctx->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ctx->base))
		return PTR_ERR(ctx->base);

	bus->name = DRV_NAME;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->read = aspeed_mdio_read;
	bus->write = aspeed_mdio_write;

	rc = of_mdiobus_register(bus, pdev->dev.of_node);
	if (rc) {
		dev_err(&pdev->dev, "Cannot register MDIO bus!\n");
		return rc;
	}

	platform_set_drvdata(pdev, bus);

	return 0;
}