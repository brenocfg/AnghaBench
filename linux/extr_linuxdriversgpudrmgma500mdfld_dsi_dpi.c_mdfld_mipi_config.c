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
struct mdfld_dsi_config {int lane_count; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DPHY_PARAM_REG (int) ; 
 int /*<<< orphan*/  MIPI_DSI_FUNC_PRG_REG (int) ; 
 int /*<<< orphan*/  MIPI_PORT_CONTROL (int) ; 
 int /*<<< orphan*/  MIPI_VIDEO_MODE_FORMAT_REG (int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdfld_mipi_set_video_timing (struct mdfld_dsi_config*,int) ; 

__attribute__((used)) static void mdfld_mipi_config(struct mdfld_dsi_config *dsi_config, int pipe)
{
	struct drm_device *dev = dsi_config->dev;
	int lane_count = dsi_config->lane_count;

	if (pipe) {
		REG_WRITE(MIPI_PORT_CONTROL(0), 0x00000002);
		REG_WRITE(MIPI_PORT_CONTROL(2), 0x80000000);
	} else {
		REG_WRITE(MIPI_PORT_CONTROL(0), 0x80010000);
		REG_WRITE(MIPI_PORT_CONTROL(2), 0x00);
	}

	REG_WRITE(MIPI_DPHY_PARAM_REG(pipe), 0x150A600F);
	REG_WRITE(MIPI_VIDEO_MODE_FORMAT_REG(pipe), 0x0000000F);

	/* lane_count = 3 */
	REG_WRITE(MIPI_DSI_FUNC_PRG_REG(pipe), 0x00000200 | lane_count);

	mdfld_mipi_set_video_timing(dsi_config, pipe);
}