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
struct sharp_nt_panel {struct mipi_dsi_device* dsi; } ;
struct mipi_dsi_device {int /*<<< orphan*/  mode_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DSI_MODE_LPM ; 
 int mipi_dsi_dcs_enter_sleep_mode (struct mipi_dsi_device*) ; 
 int mipi_dsi_dcs_set_display_off (struct mipi_dsi_device*) ; 

__attribute__((used)) static int sharp_nt_panel_off(struct sharp_nt_panel *sharp_nt)
{
	struct mipi_dsi_device *dsi = sharp_nt->dsi;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0)
		return ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0)
		return ret;

	return 0;
}