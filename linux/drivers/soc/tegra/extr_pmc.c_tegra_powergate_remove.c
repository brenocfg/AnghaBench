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
struct tegra_powergate {size_t num_clks; int /*<<< orphan*/  id; struct tegra_powergate* clks; int /*<<< orphan*/  reset; } ;
struct generic_pm_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  powergates_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (struct tegra_powergate) ; 
 int /*<<< orphan*/  kfree (struct tegra_powergate*) ; 
 TYPE_1__* pmc ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_powergate* to_powergate (struct generic_pm_domain*) ; 

__attribute__((used)) static void tegra_powergate_remove(struct generic_pm_domain *genpd)
{
	struct tegra_powergate *pg = to_powergate(genpd);

	reset_control_put(pg->reset);

	while (pg->num_clks--)
		clk_put(pg->clks[pg->num_clks]);

	kfree(pg->clks);

	set_bit(pg->id, pmc->powergates_available);

	kfree(pg);
}