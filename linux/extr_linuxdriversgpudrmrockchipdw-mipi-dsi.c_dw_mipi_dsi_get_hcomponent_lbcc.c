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
struct dw_mipi_dsi {int lane_mbps; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int MSEC_PER_SEC ; 

__attribute__((used)) static u32 dw_mipi_dsi_get_hcomponent_lbcc(struct dw_mipi_dsi *dsi,
					   struct drm_display_mode *mode,
					   u32 hcomponent)
{
	u32 frac, lbcc;

	lbcc = hcomponent * dsi->lane_mbps * MSEC_PER_SEC / 8;

	frac = lbcc % mode->clock;
	lbcc = lbcc / mode->clock;
	if (frac)
		lbcc++;

	return lbcc;
}