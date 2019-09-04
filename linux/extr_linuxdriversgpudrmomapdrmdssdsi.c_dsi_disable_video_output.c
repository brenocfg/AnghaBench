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
struct omap_dss_device {int dummy; } ;
struct dsi_data {scalar_t__ mode; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 scalar_t__ OMAP_DSS_DSI_VIDEO_MODE ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dsi_display_uninit_dispc (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  dss_mgr_disable (int /*<<< orphan*/ *) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsi_disable_video_output(struct omap_dss_device *dssdev, int channel)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);

	if (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) {
		dsi_if_enable(dsi, false);
		dsi_vc_enable(dsi, channel, false);

		/* MODE, 0 = command mode */
		REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), 0, 4, 4);

		dsi_vc_enable(dsi, channel, true);
		dsi_if_enable(dsi, true);
	}

	dss_mgr_disable(&dsi->output);

	dsi_display_uninit_dispc(dsi);
}