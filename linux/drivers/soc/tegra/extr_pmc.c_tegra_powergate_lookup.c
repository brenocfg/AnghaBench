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
struct tegra_pmc {TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_powergates; int /*<<< orphan*/ * powergates; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_is_valid (struct tegra_pmc*,unsigned int) ; 

__attribute__((used)) static int tegra_powergate_lookup(struct tegra_pmc *pmc, const char *name)
{
	unsigned int i;

	if (!pmc || !pmc->soc || !name)
		return -EINVAL;

	for (i = 0; i < pmc->soc->num_powergates; i++) {
		if (!tegra_powergate_is_valid(pmc, i))
			continue;

		if (!strcmp(name, pmc->soc->powergates[i]))
			return i;
	}

	return -ENODEV;
}