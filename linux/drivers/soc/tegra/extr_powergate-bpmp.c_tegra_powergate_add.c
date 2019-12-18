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
struct tegra_powergate_info {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; } ;
struct tegra_powergate {TYPE_1__ genpd; struct tegra_bpmp* bpmp; int /*<<< orphan*/  id; } ;
struct tegra_bpmp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tegra_powergate* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tegra_powergate* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_bpmp_powergate_is_powered (struct tegra_bpmp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off ; 
 int /*<<< orphan*/  tegra_powergate_power_on ; 

__attribute__((used)) static struct tegra_powergate *
tegra_powergate_add(struct tegra_bpmp *bpmp,
		    const struct tegra_powergate_info *info)
{
	struct tegra_powergate *powergate;
	bool off;
	int err;

	off = !tegra_bpmp_powergate_is_powered(bpmp, info->id);

	powergate = devm_kzalloc(bpmp->dev, sizeof(*powergate), GFP_KERNEL);
	if (!powergate)
		return ERR_PTR(-ENOMEM);

	powergate->id = info->id;
	powergate->bpmp = bpmp;

	powergate->genpd.name = kstrdup(info->name, GFP_KERNEL);
	powergate->genpd.power_on = tegra_powergate_power_on;
	powergate->genpd.power_off = tegra_powergate_power_off;

	err = pm_genpd_init(&powergate->genpd, NULL, off);
	if (err < 0) {
		kfree(powergate->genpd.name);
		return ERR_PTR(err);
	}

	return powergate;
}