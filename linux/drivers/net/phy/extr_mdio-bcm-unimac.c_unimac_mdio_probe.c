#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct unimac_mdio_priv {int /*<<< orphan*/ * clk; int /*<<< orphan*/  wait_func; struct unimac_mdio_priv* wait_func_data; struct mii_bus* mii_bus; scalar_t__ clk_freq; int /*<<< orphan*/  base; } ;
struct unimac_mdio_pdata {char* bus_name; int /*<<< orphan*/  phy_mask; struct unimac_mdio_priv* wait_func_data; int /*<<< orphan*/  wait_func; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {struct device_node* of_node; struct unimac_mdio_pdata* platform_data; } ;
struct platform_device {char* name; int id; TYPE_1__ dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/  id; int /*<<< orphan*/  reset; int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__* parent; int /*<<< orphan*/  phy_mask; struct unimac_mdio_priv* priv; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unimac_mdio_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct unimac_mdio_priv*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  unimac_mdio_clk_set (struct unimac_mdio_priv*) ; 
 int /*<<< orphan*/  unimac_mdio_poll ; 
 int /*<<< orphan*/  unimac_mdio_read ; 
 int /*<<< orphan*/  unimac_mdio_reset ; 
 int /*<<< orphan*/  unimac_mdio_write ; 

__attribute__((used)) static int unimac_mdio_probe(struct platform_device *pdev)
{
	struct unimac_mdio_pdata *pdata = pdev->dev.platform_data;
	struct unimac_mdio_priv *priv;
	struct device_node *np;
	struct mii_bus *bus;
	struct resource *r;
	int ret;

	np = pdev->dev.of_node;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r)
		return -EINVAL;

	/* Just ioremap, as this MDIO block is usually integrated into an
	 * Ethernet MAC controller register range
	 */
	priv->base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	if (!priv->base) {
		dev_err(&pdev->dev, "failed to remap register\n");
		return -ENOMEM;
	}

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (PTR_ERR(priv->clk) == -EPROBE_DEFER)
		return PTR_ERR(priv->clk);
	else
		priv->clk = NULL;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	if (of_property_read_u32(np, "clock-frequency", &priv->clk_freq))
		priv->clk_freq = 0;

	unimac_mdio_clk_set(priv);

	priv->mii_bus = mdiobus_alloc();
	if (!priv->mii_bus) {
		ret = -ENOMEM;
		goto out_clk_disable;
	}

	bus = priv->mii_bus;
	bus->priv = priv;
	if (pdata) {
		bus->name = pdata->bus_name;
		priv->wait_func = pdata->wait_func;
		priv->wait_func_data = pdata->wait_func_data;
		bus->phy_mask = ~pdata->phy_mask;
	} else {
		bus->name = "unimac MII bus";
		priv->wait_func_data = priv;
		priv->wait_func = unimac_mdio_poll;
	}
	bus->parent = &pdev->dev;
	bus->read = unimac_mdio_read;
	bus->write = unimac_mdio_write;
	bus->reset = unimac_mdio_reset;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);

	ret = of_mdiobus_register(bus, np);
	if (ret) {
		dev_err(&pdev->dev, "MDIO bus registration failed\n");
		goto out_mdio_free;
	}

	platform_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Broadcom UniMAC MDIO bus\n");

	return 0;

out_mdio_free:
	mdiobus_free(bus);
out_clk_disable:
	clk_disable_unprepare(priv->clk);
	return ret;
}