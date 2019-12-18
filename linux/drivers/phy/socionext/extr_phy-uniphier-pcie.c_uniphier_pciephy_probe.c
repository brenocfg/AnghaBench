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
struct uniphier_pciephy_priv {TYPE_1__* data; struct regmap* rst; struct regmap* clk; struct regmap* base; struct device* dev; } ;
struct resource {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct regmap phy ;
struct TYPE_2__ {scalar_t__ has_syscon; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  SG_USBPCIESEL ; 
 int /*<<< orphan*/  SG_USBPCIESEL_PCIE ; 
 scalar_t__ WARN_ON (int) ; 
 struct regmap* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct regmap* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct uniphier_pciephy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* devm_reset_control_get_shared (struct device*,int /*<<< orphan*/ *) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct regmap*,struct uniphier_pciephy_priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uniphier_pciephy_ops ; 

__attribute__((used)) static int uniphier_pciephy_probe(struct platform_device *pdev)
{
	struct uniphier_pciephy_priv *priv;
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	struct resource *res;
	struct phy *phy;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->data = of_device_get_match_data(dev);
	if (WARN_ON(!priv->data))
		return -EINVAL;

	priv->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	priv->rst = devm_reset_control_get_shared(dev, NULL);
	if (IS_ERR(priv->rst))
		return PTR_ERR(priv->rst);

	phy = devm_phy_create(dev, dev->of_node, &uniphier_pciephy_ops);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						 "socionext,syscon");
	if (!IS_ERR(regmap) && priv->data->has_syscon)
		regmap_update_bits(regmap, SG_USBPCIESEL,
				   SG_USBPCIESEL_PCIE, SG_USBPCIESEL_PCIE);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}