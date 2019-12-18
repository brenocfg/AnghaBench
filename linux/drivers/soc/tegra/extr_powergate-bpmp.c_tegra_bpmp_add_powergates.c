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
struct tegra_powergate_info {int dummy; } ;
struct generic_pm_domain {int /*<<< orphan*/  name; } ;
struct tegra_powergate {struct generic_pm_domain genpd; } ;
struct genpd_onecell_data {unsigned int num_domains; struct generic_pm_domain** domains; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; struct genpd_onecell_data genpd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tegra_powergate*) ; 
 int PTR_ERR (struct tegra_powergate*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct generic_pm_domain** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct generic_pm_domain**) ; 
 struct tegra_powergate* tegra_powergate_add (struct tegra_bpmp*,struct tegra_powergate_info*) ; 
 int /*<<< orphan*/  tegra_powergate_remove (struct tegra_powergate*) ; 
 struct tegra_powergate* to_tegra_powergate (struct generic_pm_domain*) ; 

__attribute__((used)) static int tegra_bpmp_add_powergates(struct tegra_bpmp *bpmp,
				     struct tegra_powergate_info *powergates,
				     unsigned int count)
{
	struct genpd_onecell_data *genpd = &bpmp->genpd;
	struct generic_pm_domain **domains;
	struct tegra_powergate *powergate;
	unsigned int i;
	int err;

	domains = kcalloc(count, sizeof(*domains), GFP_KERNEL);
	if (!domains)
		return -ENOMEM;

	for (i = 0; i < count; i++) {
		powergate = tegra_powergate_add(bpmp, &powergates[i]);
		if (IS_ERR(powergate)) {
			err = PTR_ERR(powergate);
			goto remove;
		}

		dev_dbg(bpmp->dev, "added power domain %s\n",
			powergate->genpd.name);
		domains[i] = &powergate->genpd;
	}

	genpd->num_domains = count;
	genpd->domains = domains;

	return 0;

remove:
	while (i--) {
		powergate = to_tegra_powergate(domains[i]);
		tegra_powergate_remove(powergate);
	}

	kfree(genpd->domains);
	return err;
}