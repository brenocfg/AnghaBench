#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  ddr_clk; int /*<<< orphan*/  powersave_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kirkwood_cpufreq_driver ; 
 TYPE_1__ priv ; 

__attribute__((used)) static int kirkwood_cpufreq_remove(struct platform_device *pdev)
{
	cpufreq_unregister_driver(&kirkwood_cpufreq_driver);

	clk_disable_unprepare(priv.powersave_clk);
	clk_disable_unprepare(priv.ddr_clk);
	clk_disable_unprepare(priv.cpu_clk);

	return 0;
}