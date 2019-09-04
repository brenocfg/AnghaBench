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
struct panel_desc {int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  flags; } ;
struct mipi_dsi_device {int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int innolux_panel_add (struct mipi_dsi_device*,struct panel_desc const*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 struct panel_desc* of_device_get_match_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int innolux_panel_probe(struct mipi_dsi_device *dsi)
{
	const struct panel_desc *desc;
	int err;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->flags;
	dsi->format = desc->format;
	dsi->lanes = desc->lanes;

	err = innolux_panel_add(dsi, desc);
	if (err < 0)
		return err;

	return mipi_dsi_attach(dsi);
}