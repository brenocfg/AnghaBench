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
struct spear1310_miphy_priv {struct phy_provider* phy; int /*<<< orphan*/  id; struct phy_provider* misc; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct spear1310_miphy_priv*) ; 
 struct spear1310_miphy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct spear1310_miphy_priv*) ; 
 int /*<<< orphan*/  spear1310_miphy_ops ; 
 int /*<<< orphan*/  spear1310_miphy_xlate ; 
 struct phy_provider* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int spear1310_miphy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct spear1310_miphy_priv *priv;
	struct phy_provider *phy_provider;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->misc =
		syscon_regmap_lookup_by_phandle(dev->of_node, "misc");
	if (IS_ERR(priv->misc)) {
		dev_err(dev, "failed to find misc regmap\n");
		return PTR_ERR(priv->misc);
	}

	if (of_property_read_u32(dev->of_node, "phy-id", &priv->id)) {
		dev_err(dev, "failed to find phy id\n");
		return -EINVAL;
	}

	priv->phy = devm_phy_create(dev, NULL, &spear1310_miphy_ops);
	if (IS_ERR(priv->phy)) {
		dev_err(dev, "failed to create SATA PCIe PHY\n");
		return PTR_ERR(priv->phy);
	}

	dev_set_drvdata(dev, priv);
	phy_set_drvdata(priv->phy, priv);

	phy_provider =
		devm_of_phy_provider_register(dev, spear1310_miphy_xlate);
	if (IS_ERR(phy_provider)) {
		dev_err(dev, "failed to register phy provider\n");
		return PTR_ERR(phy_provider);
	}

	return 0;
}