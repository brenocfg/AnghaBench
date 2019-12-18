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
struct dw_mipi_dsi {int dummy; } ;
struct drm_display_mode {int hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VID_PKT_SIZE ; 
 int /*<<< orphan*/  VID_PKT_SIZE (int) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dw_mipi_is_dual_mode (struct dw_mipi_dsi*) ; 

__attribute__((used)) static void dw_mipi_dsi_video_packet_config(struct dw_mipi_dsi *dsi,
					    const struct drm_display_mode *mode)
{
	/*
	 * TODO dw drv improvements
	 * only burst mode is supported here. For non-burst video modes,
	 * we should compute DSI_VID_PKT_SIZE, DSI_VCCR.NUMC &
	 * DSI_VNPCR.NPSIZE... especially because this driver supports
	 * non-burst video modes, see dw_mipi_dsi_video_mode_config()...
	 */

	dsi_write(dsi, DSI_VID_PKT_SIZE,
		       dw_mipi_is_dual_mode(dsi) ?
				VID_PKT_SIZE(mode->hdisplay / 2) :
				VID_PKT_SIZE(mode->hdisplay));
}