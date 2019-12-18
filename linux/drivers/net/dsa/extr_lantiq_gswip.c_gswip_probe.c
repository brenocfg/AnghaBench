#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct gswip_priv {int num_gphy_fw; int /*<<< orphan*/ * gphy_fw; TYPE_2__* ds; TYPE_1__* hw_info; struct device* dev; void* mii; void* mdio; void* gswip; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  slave_mii_bus; int /*<<< orphan*/ * ops; struct gswip_priv* priv; } ;
struct TYPE_6__ {int cpu_port; int /*<<< orphan*/  max_ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GSWIP_MDIO_GLOB ; 
 int /*<<< orphan*/  GSWIP_MDIO_GLOB_ENABLE ; 
 int /*<<< orphan*/  GSWIP_VERSION ; 
 int GSWIP_VERSION_MOD_MASK ; 
 int GSWIP_VERSION_MOD_SHIFT ; 
 int GSWIP_VERSION_REV_MASK ; 
 int GSWIP_VERSION_REV_SHIFT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 struct gswip_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsa_is_cpu_port (TYPE_2__*,int) ; 
 int dsa_register_switch (TYPE_2__*) ; 
 TYPE_2__* dsa_switch_alloc (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_unregister_switch (TYPE_2__*) ; 
 int gswip_gphy_fw_list (struct gswip_priv*,struct device_node*,int) ; 
 int /*<<< orphan*/  gswip_gphy_fw_remove (struct gswip_priv*,int /*<<< orphan*/ *) ; 
 int gswip_mdio (struct gswip_priv*,struct device_node*) ; 
 int /*<<< orphan*/  gswip_mdio_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_ops ; 
 int gswip_switch_r (struct gswip_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 struct device_node* of_get_compatible_child (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gswip_priv*) ; 

__attribute__((used)) static int gswip_probe(struct platform_device *pdev)
{
	struct gswip_priv *priv;
	struct device_node *mdio_np, *gphy_fw_np;
	struct device *dev = &pdev->dev;
	int err;
	int i;
	u32 version;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->gswip = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->gswip))
		return PTR_ERR(priv->gswip);

	priv->mdio = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(priv->mdio))
		return PTR_ERR(priv->mdio);

	priv->mii = devm_platform_ioremap_resource(pdev, 2);
	if (IS_ERR(priv->mii))
		return PTR_ERR(priv->mii);

	priv->hw_info = of_device_get_match_data(dev);
	if (!priv->hw_info)
		return -EINVAL;

	priv->ds = dsa_switch_alloc(dev, priv->hw_info->max_ports);
	if (!priv->ds)
		return -ENOMEM;

	priv->ds->priv = priv;
	priv->ds->ops = &gswip_switch_ops;
	priv->dev = dev;
	version = gswip_switch_r(priv, GSWIP_VERSION);

	/* bring up the mdio bus */
	gphy_fw_np = of_get_compatible_child(dev->of_node, "lantiq,gphy-fw");
	if (gphy_fw_np) {
		err = gswip_gphy_fw_list(priv, gphy_fw_np, version);
		of_node_put(gphy_fw_np);
		if (err) {
			dev_err(dev, "gphy fw probe failed\n");
			return err;
		}
	}

	/* bring up the mdio bus */
	mdio_np = of_get_compatible_child(dev->of_node, "lantiq,xrx200-mdio");
	if (mdio_np) {
		err = gswip_mdio(priv, mdio_np);
		if (err) {
			dev_err(dev, "mdio probe failed\n");
			goto put_mdio_node;
		}
	}

	err = dsa_register_switch(priv->ds);
	if (err) {
		dev_err(dev, "dsa switch register failed: %i\n", err);
		goto mdio_bus;
	}
	if (!dsa_is_cpu_port(priv->ds, priv->hw_info->cpu_port)) {
		dev_err(dev, "wrong CPU port defined, HW only supports port: %i",
			priv->hw_info->cpu_port);
		err = -EINVAL;
		goto disable_switch;
	}

	platform_set_drvdata(pdev, priv);

	dev_info(dev, "probed GSWIP version %lx mod %lx\n",
		 (version & GSWIP_VERSION_REV_MASK) >> GSWIP_VERSION_REV_SHIFT,
		 (version & GSWIP_VERSION_MOD_MASK) >> GSWIP_VERSION_MOD_SHIFT);
	return 0;

disable_switch:
	gswip_mdio_mask(priv, GSWIP_MDIO_GLOB_ENABLE, 0, GSWIP_MDIO_GLOB);
	dsa_unregister_switch(priv->ds);
mdio_bus:
	if (mdio_np)
		mdiobus_unregister(priv->ds->slave_mii_bus);
put_mdio_node:
	of_node_put(mdio_np);
	for (i = 0; i < priv->num_gphy_fw; i++)
		gswip_gphy_fw_remove(priv, &priv->gphy_fw[i]);
	return err;
}