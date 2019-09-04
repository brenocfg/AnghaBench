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
struct mdfld_dsi_dpi_timing {void* vfp_count; void* vbp_count; void* vsync_count; void* hactive_count; void* hfp_count; void* hbp_count; void* hsync_count; } ;
struct drm_display_mode {int hdisplay; int hsync_start; int hsync_end; int htotal; int vsync_start; int vdisplay; int vsync_end; int vtotal; } ;

/* Variables and functions */
 void* mdfld_dsi_dpi_to_byte_clock_count (int,int,int) ; 

int mdfld_dsi_dpi_timing_calculation(struct drm_display_mode *mode,
				struct mdfld_dsi_dpi_timing *dpi_timing,
				int num_lane, int bpp)
{
	int pclk_hsync, pclk_hfp, pclk_hbp, pclk_hactive;
	int pclk_vsync, pclk_vfp, pclk_vbp;

	pclk_hactive = mode->hdisplay;
	pclk_hfp = mode->hsync_start - mode->hdisplay;
	pclk_hsync = mode->hsync_end - mode->hsync_start;
	pclk_hbp = mode->htotal - mode->hsync_end;

	pclk_vfp = mode->vsync_start - mode->vdisplay;
	pclk_vsync = mode->vsync_end - mode->vsync_start;
	pclk_vbp = mode->vtotal - mode->vsync_end;

	/*
	 * byte clock counts were calculated by following formula
	 * bclock_count = pclk_count * bpp / num_lane / 8
	 */
	dpi_timing->hsync_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_hsync, num_lane, bpp);
	dpi_timing->hbp_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_hbp, num_lane, bpp);
	dpi_timing->hfp_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_hfp, num_lane, bpp);
	dpi_timing->hactive_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_hactive, num_lane, bpp);
	dpi_timing->vsync_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_vsync, num_lane, bpp);
	dpi_timing->vbp_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_vbp, num_lane, bpp);
	dpi_timing->vfp_count = mdfld_dsi_dpi_to_byte_clock_count(
						pclk_vfp, num_lane, bpp);

	return 0;
}