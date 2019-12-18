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
struct dw_mipi_dsi {int format; int /*<<< orphan*/  channel; } ;
struct drm_display_mode {int flags; } ;

/* Variables and functions */
 int DPI_COLOR_CODING_16BIT_1 ; 
 int DPI_COLOR_CODING_18BIT_1 ; 
 int DPI_COLOR_CODING_18BIT_2 ; 
 int DPI_COLOR_CODING_24BIT ; 
 int DPI_VCID (int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  DSI_DPI_CFG_POL ; 
 int /*<<< orphan*/  DSI_DPI_COLOR_CODING ; 
 int /*<<< orphan*/  DSI_DPI_LP_CMD_TIM ; 
 int /*<<< orphan*/  DSI_DPI_VCID ; 
 int HSYNC_ACTIVE_LOW ; 
 int INVACT_LPCMD_TIME (int) ; 
 int LOOSELY18_EN ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int OUTVACT_LPCMD_TIME (int) ; 
 int VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mipi_dsi_dpi_config(struct dw_mipi_dsi *dsi,
				   const struct drm_display_mode *mode)
{
	u32 val = 0, color = 0;

	switch (dsi->format) {
	case MIPI_DSI_FMT_RGB888:
		color = DPI_COLOR_CODING_24BIT;
		break;
	case MIPI_DSI_FMT_RGB666:
		color = DPI_COLOR_CODING_18BIT_2 | LOOSELY18_EN;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		color = DPI_COLOR_CODING_18BIT_1;
		break;
	case MIPI_DSI_FMT_RGB565:
		color = DPI_COLOR_CODING_16BIT_1;
		break;
	}

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= VSYNC_ACTIVE_LOW;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= HSYNC_ACTIVE_LOW;

	dsi_write(dsi, DSI_DPI_VCID, DPI_VCID(dsi->channel));
	dsi_write(dsi, DSI_DPI_COLOR_CODING, color);
	dsi_write(dsi, DSI_DPI_CFG_POL, val);
	/*
	 * TODO dw drv improvements
	 * largest packet sizes during hfp or during vsa/vpb/vfp
	 * should be computed according to byte lane, lane number and only
	 * if sending lp cmds in high speed is enable (PHY_TXREQUESTCLKHS)
	 */
	dsi_write(dsi, DSI_DPI_LP_CMD_TIM, OUTVACT_LPCMD_TIME(4)
		  | INVACT_LPCMD_TIME(4));
}