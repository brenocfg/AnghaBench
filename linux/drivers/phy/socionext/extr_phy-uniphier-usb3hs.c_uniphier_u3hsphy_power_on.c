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
struct uniphier_u3hsphy_priv {int /*<<< orphan*/  clk_ext; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; scalar_t__ vbus; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct uniphier_u3hsphy_priv* phy_get_drvdata (struct phy*) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_u3hsphy_power_on(struct phy *phy)
{
	struct uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = clk_prepare_enable(priv->clk_ext);
	if (ret)
		return ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		goto out_clk_ext_disable;

	ret = reset_control_deassert(priv->rst);
	if (ret)
		goto out_clk_disable;

	if (priv->vbus) {
		ret = regulator_enable(priv->vbus);
		if (ret)
			goto out_rst_assert;
	}

	return 0;

out_rst_assert:
	reset_control_assert(priv->rst);
out_clk_disable:
	clk_disable_unprepare(priv->clk);
out_clk_ext_disable:
	clk_disable_unprepare(priv->clk_ext);

	return ret;
}