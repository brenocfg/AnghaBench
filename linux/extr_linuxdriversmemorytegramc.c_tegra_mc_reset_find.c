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
struct tegra_mc_reset {unsigned long id; } ;
struct tegra_mc {TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_resets; struct tegra_mc_reset const* resets; } ;

/* Variables and functions */

__attribute__((used)) static const struct tegra_mc_reset *tegra_mc_reset_find(struct tegra_mc *mc,
							unsigned long id)
{
	unsigned int i;

	for (i = 0; i < mc->soc->num_resets; i++)
		if (mc->soc->resets[i].id == id)
			return &mc->soc->resets[i];

	return NULL;
}