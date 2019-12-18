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
struct tegra_powergate_info {struct tegra_powergate_info* name; } ;
struct TYPE_2__ {int /*<<< orphan*/  xlate; } ;
struct tegra_bpmp {TYPE_1__ genpd; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct tegra_powergate_info*) ; 
 int of_genpd_add_provider_onecell (struct device_node*,TYPE_1__*) ; 
 int tegra_bpmp_add_powergates (struct tegra_bpmp*,struct tegra_powergate_info*,unsigned int) ; 
 int tegra_bpmp_probe_powergates (struct tegra_bpmp*,struct tegra_powergate_info**) ; 
 int /*<<< orphan*/  tegra_bpmp_remove_powergates (struct tegra_bpmp*) ; 
 int /*<<< orphan*/  tegra_powergate_xlate ; 

int tegra_bpmp_init_powergates(struct tegra_bpmp *bpmp)
{
	struct device_node *np = bpmp->dev->of_node;
	struct tegra_powergate_info *powergates;
	struct device *dev = bpmp->dev;
	unsigned int count, i;
	int err;

	err = tegra_bpmp_probe_powergates(bpmp, &powergates);
	if (err < 0)
		return err;

	count = err;

	dev_dbg(dev, "%u power domains probed\n", count);

	err = tegra_bpmp_add_powergates(bpmp, powergates, count);
	if (err < 0)
		goto free;

	bpmp->genpd.xlate = tegra_powergate_xlate;

	err = of_genpd_add_provider_onecell(np, &bpmp->genpd);
	if (err < 0) {
		dev_err(dev, "failed to add power domain provider: %d\n", err);
		tegra_bpmp_remove_powergates(bpmp);
	}

free:
	for (i = 0; i < count; i++)
		kfree(powergates[i].name);

	kfree(powergates);
	return err;
}