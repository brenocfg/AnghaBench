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
struct tegra124_cpufreq_priv {int /*<<< orphan*/  pllx_clk; int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  vdd_cpu_reg; int /*<<< orphan*/  dfll_clk; int /*<<< orphan*/  pllp_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_sync_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra124_cpu_switch_to_pllx(struct tegra124_cpufreq_priv *priv)
{
	clk_set_parent(priv->cpu_clk, priv->pllp_clk);
	clk_disable_unprepare(priv->dfll_clk);
	regulator_sync_voltage(priv->vdd_cpu_reg);
	clk_set_parent(priv->cpu_clk, priv->pllx_clk);
}