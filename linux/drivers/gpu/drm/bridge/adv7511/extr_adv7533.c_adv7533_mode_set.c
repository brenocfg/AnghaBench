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
struct mipi_dsi_device {int lanes; int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int clock; } ;
struct adv7511 {int num_dsi_lanes; struct mipi_dsi_device* dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_detach (struct mipi_dsi_device*) ; 

void adv7533_mode_set(struct adv7511 *adv, const struct drm_display_mode *mode)
{
	struct mipi_dsi_device *dsi = adv->dsi;
	int lanes, ret;

	if (adv->num_dsi_lanes != 4)
		return;

	if (mode->clock > 80000)
		lanes = 4;
	else
		lanes = 3;

	if (lanes != dsi->lanes) {
		mipi_dsi_detach(dsi);
		dsi->lanes = lanes;
		ret = mipi_dsi_attach(dsi);
		if (ret)
			dev_err(&dsi->dev, "failed to change host lanes\n");
	}
}