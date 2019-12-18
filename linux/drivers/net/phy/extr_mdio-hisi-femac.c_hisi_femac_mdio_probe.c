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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {char* name; TYPE_1__ dev; } ;
struct mii_bus {char* name; struct hisi_femac_mdio_data* priv; TYPE_1__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct hisi_femac_mdio_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  membase; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_femac_mdio_read ; 
 int /*<<< orphan*/  hisi_femac_mdio_write ; 
 struct mii_bus* mdiobus_alloc_size (int) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int hisi_femac_mdio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct mii_bus *bus;
	struct hisi_femac_mdio_data *data;
	int ret;

	bus = mdiobus_alloc_size(sizeof(*data));
	if (!bus)
		return -ENOMEM;

	bus->name = "hisi_femac_mii_bus";
	bus->read = &hisi_femac_mdio_read;
	bus->write = &hisi_femac_mdio_write;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);
	bus->parent = &pdev->dev;

	data = bus->priv;
	data->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->membase)) {
		ret = PTR_ERR(data->membase);
		goto err_out_free_mdiobus;
	}

	data->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(data->clk)) {
		ret = PTR_ERR(data->clk);
		goto err_out_free_mdiobus;
	}

	ret = clk_prepare_enable(data->clk);
	if (ret)
		goto err_out_free_mdiobus;

	ret = of_mdiobus_register(bus, np);
	if (ret)
		goto err_out_disable_clk;

	platform_set_drvdata(pdev, bus);

	return 0;

err_out_disable_clk:
	clk_disable_unprepare(data->clk);
err_out_free_mdiobus:
	mdiobus_free(bus);
	return ret;
}