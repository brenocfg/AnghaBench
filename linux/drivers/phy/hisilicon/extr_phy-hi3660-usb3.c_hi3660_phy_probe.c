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
struct device {int /*<<< orphan*/  of_node; TYPE_1__* parent; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct hi3660_priv {int /*<<< orphan*/  eye_diagram_param; struct phy* otg_bc; struct phy* pctrl; struct phy* peri_crg; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HI3660_USB_DEFAULT_PHY_PARAM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct hi3660_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hi3660_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct hi3660_priv*) ; 
 struct phy* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 void* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hi3660_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct phy *phy;
	struct hi3660_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;
	priv->peri_crg = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,pericrg-syscon");
	if (IS_ERR(priv->peri_crg)) {
		dev_err(dev, "no hisilicon,pericrg-syscon\n");
		return PTR_ERR(priv->peri_crg);
	}

	priv->pctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,pctrl-syscon");
	if (IS_ERR(priv->pctrl)) {
		dev_err(dev, "no hisilicon,pctrl-syscon\n");
		return PTR_ERR(priv->pctrl);
	}

	/* node of hi3660 phy is a sub-node of usb3_otg_bc */
	priv->otg_bc = syscon_node_to_regmap(dev->parent->of_node);
	if (IS_ERR(priv->otg_bc)) {
		dev_err(dev, "no hisilicon,usb3-otg-bc-syscon\n");
		return PTR_ERR(priv->otg_bc);
	}

	if (of_property_read_u32(dev->of_node, "hisilicon,eye-diagram-param",
		&(priv->eye_diagram_param)))
		priv->eye_diagram_param = HI3660_USB_DEFAULT_PHY_PARAM;

	phy = devm_phy_create(dev, NULL, &hi3660_phy_ops);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}