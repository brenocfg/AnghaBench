#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mv88e6060_priv {int /*<<< orphan*/  sw_addr; int /*<<< orphan*/  bus; } ;
struct device {int dummy; } ;
struct mdio_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; struct device dev; } ;
struct dsa_switch {int /*<<< orphan*/ * ops; struct device* dev; struct mv88e6060_priv* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MV88E6060_PORTS ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dsa_switch*) ; 
 struct mv88e6060_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dsa_register_switch (struct dsa_switch*) ; 
 struct dsa_switch* dsa_switch_alloc (struct device*,int /*<<< orphan*/ ) ; 
 char* mv88e6060_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6060_switch_ops ; 

__attribute__((used)) static int mv88e6060_probe(struct mdio_device *mdiodev)
{
	struct device *dev = &mdiodev->dev;
	struct mv88e6060_priv *priv;
	struct dsa_switch *ds;
	const char *name;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->bus = mdiodev->bus;
	priv->sw_addr = mdiodev->addr;

	name = mv88e6060_get_name(priv->bus, priv->sw_addr);
	if (!name)
		return -ENODEV;

	dev_info(dev, "switch %s detected\n", name);

	ds = dsa_switch_alloc(dev, MV88E6060_PORTS);
	if (!ds)
		return -ENOMEM;

	ds->priv = priv;
	ds->dev = dev;
	ds->ops = &mv88e6060_switch_ops;

	dev_set_drvdata(dev, ds);

	return dsa_register_switch(ds);
}