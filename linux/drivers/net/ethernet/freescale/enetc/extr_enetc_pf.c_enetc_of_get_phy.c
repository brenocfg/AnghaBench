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
struct enetc_pf {int dummy; } ;
struct enetc_ndev_priv {struct device_node* phy_node; TYPE_1__* dev; scalar_t__ if_mode; int /*<<< orphan*/  si; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int enetc_mdio_probe (struct enetc_pf*) ; 
 int /*<<< orphan*/  enetc_mdio_remove (struct enetc_pf*) ; 
 struct enetc_pf* enetc_si_priv (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 scalar_t__ of_get_phy_mode (struct device_node*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 

__attribute__((used)) static int enetc_of_get_phy(struct enetc_ndev_priv *priv)
{
	struct enetc_pf *pf = enetc_si_priv(priv->si);
	struct device_node *np = priv->dev->of_node;
	struct device_node *mdio_np;
	int err;

	if (!np) {
		dev_err(priv->dev, "missing ENETC port node\n");
		return -ENODEV;
	}

	priv->phy_node = of_parse_phandle(np, "phy-handle", 0);
	if (!priv->phy_node) {
		if (!of_phy_is_fixed_link(np)) {
			dev_err(priv->dev, "PHY not specified\n");
			return -ENODEV;
		}

		err = of_phy_register_fixed_link(np);
		if (err < 0) {
			dev_err(priv->dev, "fixed link registration failed\n");
			return err;
		}

		priv->phy_node = of_node_get(np);
	}

	mdio_np = of_get_child_by_name(np, "mdio");
	if (mdio_np) {
		of_node_put(mdio_np);
		err = enetc_mdio_probe(pf);
		if (err) {
			of_node_put(priv->phy_node);
			return err;
		}
	}

	priv->if_mode = of_get_phy_mode(np);
	if ((int)priv->if_mode < 0) {
		dev_err(priv->dev, "missing phy type\n");
		of_node_put(priv->phy_node);
		if (of_phy_is_fixed_link(np))
			of_phy_deregister_fixed_link(np);
		else
			enetc_mdio_remove(pf);

		return -EINVAL;
	}

	return 0;
}