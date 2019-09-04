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
typedef  int u32 ;
struct msm_dsi_host {struct drm_display_mode* mode; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */

__attribute__((used)) static u32 dsi_get_pclk_rate(struct msm_dsi_host *msm_host, bool is_dual_dsi)
{
	struct drm_display_mode *mode = msm_host->mode;
	u32 pclk_rate;

	pclk_rate = mode->clock * 1000;

	/*
	 * For dual DSI mode, the current DRM mode has the complete width of the
	 * panel. Since, the complete panel is driven by two DSI controllers,
	 * the clock rates have to be split between the two dsi controllers.
	 * Adjust the byte and pixel clock rates for each dsi host accordingly.
	 */
	if (is_dual_dsi)
		pclk_rate /= 2;

	return pclk_rate;
}