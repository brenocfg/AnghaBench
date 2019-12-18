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
struct dw_mipi_dsi {int /*<<< orphan*/  mode_flags; struct dw_mipi_dsi* slave; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; int /*<<< orphan*/  lanes; struct dw_mipi_dsi* master; } ;

/* Variables and functions */

void dw_mipi_dsi_set_slave(struct dw_mipi_dsi *dsi, struct dw_mipi_dsi *slave)
{
	/* introduce controllers to each other */
	dsi->slave = slave;
	dsi->slave->master = dsi;

	/* migrate settings for already attached displays */
	dsi->slave->lanes = dsi->lanes;
	dsi->slave->channel = dsi->channel;
	dsi->slave->format = dsi->format;
	dsi->slave->mode_flags = dsi->mode_flags;
}