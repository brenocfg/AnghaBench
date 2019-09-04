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
struct tegra_windowgroup {int dummy; } ;
struct tegra_display_hub {struct tegra_windowgroup* wgrps; TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_wgrps; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_windowgroup_disable (struct tegra_windowgroup*) ; 

void tegra_display_hub_cleanup(struct tegra_display_hub *hub)
{
	unsigned int i;

	/*
	 * XXX Remove this once window groups can be more fine-grainedly
	 * enabled and disabled.
	 */
	for (i = 0; i < hub->soc->num_wgrps; i++) {
		struct tegra_windowgroup *wgrp = &hub->wgrps[i];

		tegra_windowgroup_disable(wgrp);
	}
}