#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct ltq_rcu_usb2_priv {int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  ctrl_reset; int /*<<< orphan*/  phy_gate_clk; void* ana_cfg1_reg_offset; TYPE_2__* reg_bits; void* phy_reg_offset; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct device {TYPE_1__* of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ have_ana_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 void* __be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_shared (struct device*,char*) ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/ * of_get_address (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_rcu_usb2_of_parse(struct ltq_rcu_usb2_priv *priv,
				 struct platform_device *pdev)
{
	struct device *dev = priv->dev;
	const __be32 *offset;

	priv->reg_bits = of_device_get_match_data(dev);

	priv->regmap = syscon_node_to_regmap(dev->of_node->parent);
	if (IS_ERR(priv->regmap)) {
		dev_err(dev, "Failed to lookup RCU regmap\n");
		return PTR_ERR(priv->regmap);
	}

	offset = of_get_address(dev->of_node, 0, NULL, NULL);
	if (!offset) {
		dev_err(dev, "Failed to get RCU PHY reg offset\n");
		return -ENOENT;
	}
	priv->phy_reg_offset = __be32_to_cpu(*offset);

	if (priv->reg_bits->have_ana_cfg) {
		offset = of_get_address(dev->of_node, 1, NULL, NULL);
		if (!offset) {
			dev_err(dev, "Failed to get RCU ANA CFG1 reg offset\n");
			return -ENOENT;
		}
		priv->ana_cfg1_reg_offset = __be32_to_cpu(*offset);
	}

	priv->phy_gate_clk = devm_clk_get(dev, "phy");
	if (IS_ERR(priv->phy_gate_clk)) {
		dev_err(dev, "Unable to get USB phy gate clk\n");
		return PTR_ERR(priv->phy_gate_clk);
	}

	priv->ctrl_reset = devm_reset_control_get_shared(dev, "ctrl");
	if (IS_ERR(priv->ctrl_reset)) {
		if (PTR_ERR(priv->ctrl_reset) != -EPROBE_DEFER)
			dev_err(dev, "failed to get 'ctrl' reset\n");
		return PTR_ERR(priv->ctrl_reset);
	}

	priv->phy_reset = devm_reset_control_get_optional(dev, "phy");

	return PTR_ERR_OR_ZERO(priv->phy_reset);
}