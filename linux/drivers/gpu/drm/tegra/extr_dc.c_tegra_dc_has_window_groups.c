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
struct tegra_windowgroup_soc {scalar_t__ dc; scalar_t__ num_windows; } ;
struct tegra_dc {scalar_t__ pipe; TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_wgrps; struct tegra_windowgroup_soc* wgrps; } ;

/* Variables and functions */

__attribute__((used)) static bool tegra_dc_has_window_groups(struct tegra_dc *dc)
{
	unsigned int i;

	if (!dc->soc->wgrps)
		return true;

	for (i = 0; i < dc->soc->num_wgrps; i++) {
		const struct tegra_windowgroup_soc *wgrp = &dc->soc->wgrps[i];

		if (wgrp->dc == dc->pipe && wgrp->num_windows > 0)
			return true;
	}

	return false;
}