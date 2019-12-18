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
struct uniphier_pcie_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_pcie_init_rc (struct uniphier_pcie_priv*) ; 
 int uniphier_pcie_wait_rc (struct uniphier_pcie_priv*) ; 

__attribute__((used)) static int uniphier_pcie_host_enable(struct uniphier_pcie_priv *priv)
{
	int ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret)
		return ret;

	ret = reset_control_deassert(priv->rst);
	if (ret)
		goto out_clk_disable;

	uniphier_pcie_init_rc(priv);

	ret = phy_init(priv->phy);
	if (ret)
		goto out_rst_assert;

	ret = uniphier_pcie_wait_rc(priv);
	if (ret)
		goto out_phy_exit;

	return 0;

out_phy_exit:
	phy_exit(priv->phy);
out_rst_assert:
	reset_control_assert(priv->rst);
out_clk_disable:
	clk_disable_unprepare(priv->clk);

	return ret;
}