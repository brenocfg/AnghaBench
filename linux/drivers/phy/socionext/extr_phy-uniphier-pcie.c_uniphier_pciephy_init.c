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
struct uniphier_pciephy_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCL_PHY_R00 ; 
 int /*<<< orphan*/  PCL_PHY_R06 ; 
 int /*<<< orphan*/  PCL_PHY_R26 ; 
 int /*<<< orphan*/  RX_EQ_ADJ ; 
 int /*<<< orphan*/  RX_EQ_ADJ_EN ; 
 int /*<<< orphan*/  RX_EQ_ADJ_VAL ; 
 int /*<<< orphan*/  VCO_CTRL ; 
 int /*<<< orphan*/  VCO_CTRL_INIT_VAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct uniphier_pciephy_priv* phy_get_drvdata (struct phy*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_pciephy_deassert (struct uniphier_pciephy_priv*) ; 
 int /*<<< orphan*/  uniphier_pciephy_set_param (struct uniphier_pciephy_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int uniphier_pciephy_init(struct phy *phy)
{
	struct uniphier_pciephy_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	ret = reset_control_deassert(priv->rst);
	if (ret)
		goto out_clk_disable;

	uniphier_pciephy_set_param(priv, PCL_PHY_R00,
				   RX_EQ_ADJ_EN, RX_EQ_ADJ_EN);
	uniphier_pciephy_set_param(priv, PCL_PHY_R06, RX_EQ_ADJ,
				   FIELD_PREP(RX_EQ_ADJ, RX_EQ_ADJ_VAL));
	uniphier_pciephy_set_param(priv, PCL_PHY_R26, VCO_CTRL,
				   FIELD_PREP(VCO_CTRL, VCO_CTRL_INIT_VAL));
	usleep_range(1, 10);

	uniphier_pciephy_deassert(priv);
	usleep_range(1, 10);

	return 0;

out_clk_disable:
	clk_disable_unprepare(priv->clk);

	return ret;
}