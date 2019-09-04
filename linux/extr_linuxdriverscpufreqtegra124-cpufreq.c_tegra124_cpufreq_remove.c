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
struct tegra124_cpufreq_priv {int /*<<< orphan*/  vdd_cpu_reg; int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  dfll_clk; int /*<<< orphan*/  pllx_clk; int /*<<< orphan*/  pllp_clk; int /*<<< orphan*/  cpufreq_dt_pdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct tegra124_cpufreq_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra124_cpu_switch_to_pllx (struct tegra124_cpufreq_priv*) ; 

__attribute__((used)) static int tegra124_cpufreq_remove(struct platform_device *pdev)
{
	struct tegra124_cpufreq_priv *priv = platform_get_drvdata(pdev);

	platform_device_unregister(priv->cpufreq_dt_pdev);
	tegra124_cpu_switch_to_pllx(priv);

	clk_put(priv->pllp_clk);
	clk_put(priv->pllx_clk);
	clk_put(priv->dfll_clk);
	clk_put(priv->cpu_clk);
	regulator_put(priv->vdd_cpu_reg);

	return 0;
}