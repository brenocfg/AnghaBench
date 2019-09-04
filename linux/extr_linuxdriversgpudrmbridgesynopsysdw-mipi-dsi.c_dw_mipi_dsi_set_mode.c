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

/* Variables and functions */
 int /*<<< orphan*/  DSI_LPCLK_CTRL ; 
 int /*<<< orphan*/  DSI_MODE_CFG ; 
 int /*<<< orphan*/  DSI_PWR_UP ; 
 int /*<<< orphan*/  ENABLE_CMD_MODE ; 
 int /*<<< orphan*/  ENABLE_VIDEO_MODE ; 
 unsigned long MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  PHY_TXREQUESTCLKHS ; 
 int /*<<< orphan*/  POWERUP ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_video_mode_config (struct dw_mipi_dsi*) ; 

__attribute__((used)) static void dw_mipi_dsi_set_mode(struct dw_mipi_dsi *dsi,
				 unsigned long mode_flags)
{
	dsi_write(dsi, DSI_PWR_UP, RESET);

	if (mode_flags & MIPI_DSI_MODE_VIDEO) {
		dsi_write(dsi, DSI_MODE_CFG, ENABLE_VIDEO_MODE);
		dw_mipi_dsi_video_mode_config(dsi);
		dsi_write(dsi, DSI_LPCLK_CTRL, PHY_TXREQUESTCLKHS);
	} else {
		dsi_write(dsi, DSI_MODE_CFG, ENABLE_CMD_MODE);
	}

	dsi_write(dsi, DSI_PWR_UP, POWERUP);
}