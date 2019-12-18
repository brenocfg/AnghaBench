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
struct sun4i_mdio_data {int /*<<< orphan*/ * regulator; int /*<<< orphan*/ * membase; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mii_bus {char* name; struct sun4i_mdio_data* priv; TYPE_1__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 char* dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get (TYPE_1__*,char*) ; 
 struct mii_bus* mdiobus_alloc_size (int) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sun4i_mdio_read ; 
 int /*<<< orphan*/  sun4i_mdio_write ; 

__attribute__((used)) static int sun4i_mdio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct mii_bus *bus;
	struct sun4i_mdio_data *data;
	int ret;

	bus = mdiobus_alloc_size(sizeof(*data));
	if (!bus)
		return -ENOMEM;

	bus->name = "sun4i_mii_bus";
	bus->read = &sun4i_mdio_read;
	bus->write = &sun4i_mdio_write;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	data = bus->priv;
	data->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->membase)) {
		ret = PTR_ERR(data->membase);
		goto err_out_free_mdiobus;
	}

	data->regulator = devm_regulator_get(&pdev->dev, "phy");
	if (IS_ERR(data->regulator)) {
		if (PTR_ERR(data->regulator) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto err_out_free_mdiobus;
		}

		dev_info(&pdev->dev, "no regulator found\n");
		data->regulator = NULL;
	} else {
		ret = regulator_enable(data->regulator);
		if (ret)
			goto err_out_free_mdiobus;
	}

	ret = of_mdiobus_register(bus, np);
	if (ret < 0)
		goto err_out_disable_regulator;

	platform_set_drvdata(pdev, bus);

	return 0;

err_out_disable_regulator:
	if (data->regulator)
		regulator_disable(data->regulator);
err_out_free_mdiobus:
	mdiobus_free(bus);
	return ret;
}