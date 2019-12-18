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
struct mvebu_comphy_priv {scalar_t__ mg_domain_clk; scalar_t__ mg_core_clk; scalar_t__ axi_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

__attribute__((used)) static void mvebu_comphy_disable_unprepare_clks(struct mvebu_comphy_priv *priv)
{
	if (priv->axi_clk)
		clk_disable_unprepare(priv->axi_clk);

	if (priv->mg_core_clk)
		clk_disable_unprepare(priv->mg_core_clk);

	if (priv->mg_domain_clk)
		clk_disable_unprepare(priv->mg_domain_clk);
}