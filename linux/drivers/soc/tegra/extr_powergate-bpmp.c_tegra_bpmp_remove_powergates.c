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
struct tegra_powergate {int dummy; } ;
struct genpd_onecell_data {unsigned int num_domains; TYPE_1__** domains; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; struct genpd_onecell_data genpd; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_remove (struct tegra_powergate*) ; 
 struct tegra_powergate* to_tegra_powergate (TYPE_1__*) ; 

__attribute__((used)) static void tegra_bpmp_remove_powergates(struct tegra_bpmp *bpmp)
{
	struct genpd_onecell_data *genpd = &bpmp->genpd;
	unsigned int i = genpd->num_domains;
	struct tegra_powergate *powergate;

	while (i--) {
		dev_dbg(bpmp->dev, "removing power domain %s\n",
			genpd->domains[i]->name);
		powergate = to_tegra_powergate(genpd->domains[i]);
		tegra_powergate_remove(powergate);
	}
}