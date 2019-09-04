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
struct exynos_bus {int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct exynos_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (struct device*) ; 

__attribute__((used)) static void exynos_bus_passive_exit(struct device *dev)
{
	struct exynos_bus *bus = dev_get_drvdata(dev);

	dev_pm_opp_of_remove_table(dev);
	clk_disable_unprepare(bus->clk);
}