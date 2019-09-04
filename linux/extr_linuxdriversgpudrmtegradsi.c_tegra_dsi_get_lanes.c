#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_dsi {unsigned int lanes; TYPE_2__* slave; TYPE_1__* master; } ;
struct TYPE_4__ {unsigned int lanes; } ;
struct TYPE_3__ {unsigned int lanes; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int tegra_dsi_get_lanes(struct tegra_dsi *dsi)
{
	if (dsi->master)
		return dsi->master->lanes + dsi->lanes;

	if (dsi->slave)
		return dsi->lanes + dsi->slave->lanes;

	return dsi->lanes;
}