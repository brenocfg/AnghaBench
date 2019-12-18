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
typedef  int /*<<< orphan*/  u32 ;
struct dw_mipi_dsi {int mode_flags; scalar_t__ vpg_horizontal; scalar_t__ vpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VID_MODE_CFG ; 
 int /*<<< orphan*/  ENABLE_LOW_POWER ; 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 int /*<<< orphan*/  VID_MODE_TYPE_BURST ; 
 int /*<<< orphan*/  VID_MODE_TYPE_NON_BURST_SYNC_EVENTS ; 
 int /*<<< orphan*/  VID_MODE_TYPE_NON_BURST_SYNC_PULSES ; 
 int /*<<< orphan*/  VID_MODE_VPG_ENABLE ; 
 int /*<<< orphan*/  VID_MODE_VPG_HORIZONTAL ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_video_mode_config(struct dw_mipi_dsi *dsi)
{
	u32 val;

	/*
	 * TODO dw drv improvements
	 * enabling low power is panel-dependent, we should use the
	 * panel configuration here...
	 */
	val = ENABLE_LOW_POWER;

	if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		val |= VID_MODE_TYPE_BURST;
	else if (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		val |= VID_MODE_TYPE_NON_BURST_SYNC_PULSES;
	else
		val |= VID_MODE_TYPE_NON_BURST_SYNC_EVENTS;

#ifdef CONFIG_DEBUG_FS
	if (dsi->vpg) {
		val |= VID_MODE_VPG_ENABLE;
		val |= dsi->vpg_horizontal ? VID_MODE_VPG_HORIZONTAL : 0;
	}
#endif /* CONFIG_DEBUG_FS */

	dsi_write(dsi, DSI_VID_MODE_CFG, val);
}