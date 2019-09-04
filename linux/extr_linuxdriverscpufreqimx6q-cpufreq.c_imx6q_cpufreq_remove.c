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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_reg ; 
 int /*<<< orphan*/  clk_bulk_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clks ; 
 int /*<<< orphan*/  cpu_dev ; 
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_free_cpufreq_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (int /*<<< orphan*/ ) ; 
 scalar_t__ free_opp ; 
 int /*<<< orphan*/  freq_table ; 
 int /*<<< orphan*/  imx6q_cpufreq_driver ; 
 int /*<<< orphan*/  num_clks ; 
 int /*<<< orphan*/  pu_reg ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_reg ; 

__attribute__((used)) static int imx6q_cpufreq_remove(struct platform_device *pdev)
{
	cpufreq_unregister_driver(&imx6q_cpufreq_driver);
	dev_pm_opp_free_cpufreq_table(cpu_dev, &freq_table);
	if (free_opp)
		dev_pm_opp_of_remove_table(cpu_dev);
	regulator_put(arm_reg);
	if (!IS_ERR(pu_reg))
		regulator_put(pu_reg);
	regulator_put(soc_reg);

	clk_bulk_put(num_clks, clks);

	return 0;
}