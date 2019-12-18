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
struct dw_mipi_dsi {unsigned int lanes; TYPE_2__* slave; TYPE_1__* master; } ;
struct TYPE_4__ {unsigned int lanes; } ;
struct TYPE_3__ {unsigned int lanes; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int dw_mipi_dsi_get_lanes(struct dw_mipi_dsi *dsi)
{
	/* this instance is the slave, so add the master's lanes */
	if (dsi->master)
		return dsi->master->lanes + dsi->lanes;

	/* this instance is the master, so add the slave's lanes */
	if (dsi->slave)
		return dsi->lanes + dsi->slave->lanes;

	/* single-dsi, so no other instance to consider */
	return dsi->lanes;
}