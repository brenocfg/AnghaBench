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
struct tegra20_cpufreq {int /*<<< orphan*/  cpu_clk; } ;
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tegra20_cpufreq* cpufreq_get_driver_data () ; 

__attribute__((used)) static int tegra_cpu_exit(struct cpufreq_policy *policy)
{
	struct tegra20_cpufreq *cpufreq = cpufreq_get_driver_data();

	clk_disable_unprepare(cpufreq->cpu_clk);
	return 0;
}