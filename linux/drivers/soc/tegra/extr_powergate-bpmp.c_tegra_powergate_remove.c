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
struct generic_pm_domain {int /*<<< orphan*/  name; } ;
struct tegra_powergate {struct tegra_bpmp* bpmp; struct generic_pm_domain genpd; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int pm_genpd_remove (struct generic_pm_domain*) ; 

__attribute__((used)) static void tegra_powergate_remove(struct tegra_powergate *powergate)
{
	struct generic_pm_domain *genpd = &powergate->genpd;
	struct tegra_bpmp *bpmp = powergate->bpmp;
	int err;

	err = pm_genpd_remove(genpd);
	if (err < 0)
		dev_err(bpmp->dev, "failed to remove power domain %s: %d\n",
			genpd->name, err);

	kfree(genpd->name);
}