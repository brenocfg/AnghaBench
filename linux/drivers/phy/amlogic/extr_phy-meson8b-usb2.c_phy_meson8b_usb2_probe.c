#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct phy_provider {int dummy; } ;
struct phy_meson8b_usb2_priv {scalar_t__ dr_mode; struct phy* reset; struct phy* clk_usb; struct phy* clk_usb_general; struct phy* regs; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 scalar_t__ USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct phy* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct phy_meson8b_usb2_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy* devm_reset_control_get_optional_shared (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 scalar_t__ of_usb_get_dr_mode_by_phy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_meson8b_usb2_ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct phy_meson8b_usb2_priv*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson8b_usb2_probe(struct platform_device *pdev)
{
	struct phy_meson8b_usb2_priv *priv;
	struct resource *res;
	struct phy *phy;
	struct phy_provider *phy_provider;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->regs))
		return PTR_ERR(priv->regs);

	priv->clk_usb_general = devm_clk_get(&pdev->dev, "usb_general");
	if (IS_ERR(priv->clk_usb_general))
		return PTR_ERR(priv->clk_usb_general);

	priv->clk_usb = devm_clk_get(&pdev->dev, "usb");
	if (IS_ERR(priv->clk_usb))
		return PTR_ERR(priv->clk_usb);

	priv->reset = devm_reset_control_get_optional_shared(&pdev->dev, NULL);
	if (PTR_ERR(priv->reset) == -EPROBE_DEFER)
		return PTR_ERR(priv->reset);

	priv->dr_mode = of_usb_get_dr_mode_by_phy(pdev->dev.of_node, -1);
	if (priv->dr_mode == USB_DR_MODE_UNKNOWN) {
		dev_err(&pdev->dev,
			"missing dual role configuration of the controller\n");
		return -EINVAL;
	}

	phy = devm_phy_create(&pdev->dev, NULL, &phy_meson8b_usb2_ops);
	if (IS_ERR(phy)) {
		dev_err(&pdev->dev, "failed to create PHY\n");
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, priv);

	phy_provider =
		devm_of_phy_provider_register(&pdev->dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}