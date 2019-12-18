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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct ltq_rcu_usb2_priv {struct device* dev; struct phy_provider* phy; int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  ctrl_reset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ltq_rcu_usb2_priv*) ; 
 struct ltq_rcu_usb2_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltq_rcu_usb2_of_parse (struct ltq_rcu_usb2_priv*,struct platform_device*) ; 
 int /*<<< orphan*/  ltq_rcu_usb2_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct ltq_rcu_usb2_priv*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_rcu_usb2_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ltq_rcu_usb2_priv *priv;
	struct phy_provider *provider;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;

	ret = ltq_rcu_usb2_of_parse(priv, pdev);
	if (ret)
		return ret;

	/* Reset USB core through reset controller */
	reset_control_deassert(priv->ctrl_reset);

	reset_control_assert(priv->phy_reset);

	priv->phy = devm_phy_create(dev, dev->of_node, &ltq_rcu_usb2_phy_ops);
	if (IS_ERR(priv->phy)) {
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(priv->phy);
	}

	phy_set_drvdata(priv->phy, priv);

	provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (IS_ERR(provider))
		return PTR_ERR(provider);

	dev_set_drvdata(priv->dev, priv);
	return 0;
}