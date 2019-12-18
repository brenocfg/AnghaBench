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
struct platform_device {char* name; int id; TYPE_1__ dev; } ;
struct moxart_mdio_data {int /*<<< orphan*/  base; } ;
struct mii_bus {char* name; struct moxart_mdio_data* priv; int /*<<< orphan*/ * irq; TYPE_1__* parent; int /*<<< orphan*/  id; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  PHY_IGNORE_INTERRUPT ; 
 int PHY_MAX_ADDR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdiobus_alloc_size (int) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  moxart_mdio_read ; 
 int /*<<< orphan*/  moxart_mdio_reset ; 
 int /*<<< orphan*/  moxart_mdio_write ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int moxart_mdio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct mii_bus *bus;
	struct moxart_mdio_data *data;
	int ret, i;

	bus = mdiobus_alloc_size(sizeof(*data));
	if (!bus)
		return -ENOMEM;

	bus->name = "MOXA ART Ethernet MII";
	bus->read = &moxart_mdio_read;
	bus->write = &moxart_mdio_write;
	bus->reset = &moxart_mdio_reset;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-%d-mii", pdev->name, pdev->id);
	bus->parent = &pdev->dev;

	/* Setting PHY_IGNORE_INTERRUPT here even if it has no effect,
	 * of_mdiobus_register() sets these PHY_POLL.
	 * Ideally, the interrupt from MAC controller could be used to
	 * detect link state changes, not polling, i.e. if there was
	 * a way phy_driver could set PHY_HAS_INTERRUPT but have that
	 * interrupt handled in ethernet drivercode.
	 */
	for (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = PHY_IGNORE_INTERRUPT;

	data = bus->priv;
	data->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(data->base)) {
		ret = PTR_ERR(data->base);
		goto err_out_free_mdiobus;
	}

	ret = of_mdiobus_register(bus, np);
	if (ret < 0)
		goto err_out_free_mdiobus;

	platform_set_drvdata(pdev, bus);

	return 0;

err_out_free_mdiobus:
	mdiobus_free(bus);
	return ret;
}