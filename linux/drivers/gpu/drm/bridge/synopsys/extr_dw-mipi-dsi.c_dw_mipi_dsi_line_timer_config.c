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
typedef  scalar_t__ u32 ;
struct dw_mipi_dsi {int dummy; } ;
struct drm_display_mode {scalar_t__ hsync_end; scalar_t__ htotal; scalar_t__ hsync_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VID_HBP_TIME ; 
 int /*<<< orphan*/  DSI_VID_HLINE_TIME ; 
 int /*<<< orphan*/  DSI_VID_HSA_TIME ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dw_mipi_dsi_get_hcomponent_lbcc (struct dw_mipi_dsi*,struct drm_display_mode const*,scalar_t__) ; 

__attribute__((used)) static void dw_mipi_dsi_line_timer_config(struct dw_mipi_dsi *dsi,
					  const struct drm_display_mode *mode)
{
	u32 htotal, hsa, hbp, lbcc;

	htotal = mode->htotal;
	hsa = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_end;

	/*
	 * TODO dw drv improvements
	 * computations below may be improved...
	 */
	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, htotal);
	dsi_write(dsi, DSI_VID_HLINE_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, hsa);
	dsi_write(dsi, DSI_VID_HSA_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(dsi, mode, hbp);
	dsi_write(dsi, DSI_VID_HBP_TIME, lbcc);
}