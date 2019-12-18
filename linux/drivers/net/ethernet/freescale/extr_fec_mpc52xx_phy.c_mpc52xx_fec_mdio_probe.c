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
struct resource {int start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct mpc52xx_fec_mdio_priv {TYPE_1__* regs; } ;
struct mii_bus {char* name; struct device* parent; struct mpc52xx_fec_mdio_priv* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mii_speed; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct mii_bus*) ; 
 TYPE_1__* ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct mpc52xx_fec_mdio_priv*) ; 
 struct mpc52xx_fec_mdio_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mpc52xx_fec_mdio_read ; 
 int /*<<< orphan*/  mpc52xx_fec_mdio_write ; 
 int mpc5xxx_get_bus_frequency (struct device_node*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mpc52xx_fec_mdio_probe(struct platform_device *of)
{
	struct device *dev = &of->dev;
	struct device_node *np = of->dev.of_node;
	struct mii_bus *bus;
	struct mpc52xx_fec_mdio_priv *priv;
	struct resource res;
	int err;

	bus = mdiobus_alloc();
	if (bus == NULL)
		return -ENOMEM;
	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL) {
		err = -ENOMEM;
		goto out_free;
	}

	bus->name = "mpc52xx MII bus";
	bus->read = mpc52xx_fec_mdio_read;
	bus->write = mpc52xx_fec_mdio_write;

	/* setup registers */
	err = of_address_to_resource(np, 0, &res);
	if (err)
		goto out_free;
	priv->regs = ioremap(res.start, resource_size(&res));
	if (priv->regs == NULL) {
		err = -ENOMEM;
		goto out_free;
	}

	snprintf(bus->id, MII_BUS_ID_SIZE, "%x", res.start);
	bus->priv = priv;

	bus->parent = dev;
	dev_set_drvdata(dev, bus);

	/* set MII speed */
	out_be32(&priv->regs->mii_speed,
		((mpc5xxx_get_bus_frequency(of->dev.of_node) >> 20) / 5) << 1);

	err = of_mdiobus_register(bus, np);
	if (err)
		goto out_unmap;

	return 0;

 out_unmap:
	iounmap(priv->regs);
 out_free:
	kfree(priv);
	mdiobus_free(bus);

	return err;
}