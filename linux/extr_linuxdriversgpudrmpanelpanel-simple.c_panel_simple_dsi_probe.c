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
struct panel_desc_dsi {int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  flags; int /*<<< orphan*/  desc; } ;
struct of_device_id {struct panel_desc_dsi* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  mode_flags; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dsi_of_match ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int panel_simple_probe (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_simple_dsi_probe(struct mipi_dsi_device *dsi)
{
	const struct panel_desc_dsi *desc;
	const struct of_device_id *id;
	int err;

	id = of_match_node(dsi_of_match, dsi->dev.of_node);
	if (!id)
		return -ENODEV;

	desc = id->data;

	err = panel_simple_probe(&dsi->dev, &desc->desc);
	if (err < 0)
		return err;

	dsi->mode_flags = desc->flags;
	dsi->format = desc->format;
	dsi->lanes = desc->lanes;

	return mipi_dsi_attach(dsi);
}