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
struct mdfld_dsi_config {int bpp; int lane_count; int /*<<< orphan*/  video_mode; scalar_t__ channel_num; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDFLD_DSI_VIDEO_BURST_MODE ; 
 int /*<<< orphan*/  MDFLD_DSI_VIDEO_NON_BURST_MODE_SYNC_EVENTS ; 
 int /*<<< orphan*/  MDFLD_DSI_VIDEO_NON_BURST_MODE_SYNC_PULSE ; 
 scalar_t__ TC35876X ; 
 scalar_t__ TMD_VID ; 
 scalar_t__ mdfld_get_panel_type (struct drm_device*,int) ; 

__attribute__((used)) static int mdfld_dsi_get_default_config(struct drm_device *dev,
				struct mdfld_dsi_config *config, int pipe)
{
	if (!dev || !config) {
		DRM_ERROR("Invalid parameters");
		return -EINVAL;
	}

	config->bpp = 24;
	if (mdfld_get_panel_type(dev, pipe) == TC35876X)
		config->lane_count = 4;
	else
		config->lane_count = 2;
	config->channel_num = 0;

	if (mdfld_get_panel_type(dev, pipe) == TMD_VID)
		config->video_mode = MDFLD_DSI_VIDEO_NON_BURST_MODE_SYNC_PULSE;
	else if (mdfld_get_panel_type(dev, pipe) == TC35876X)
		config->video_mode =
				MDFLD_DSI_VIDEO_NON_BURST_MODE_SYNC_EVENTS;
	else
		config->video_mode = MDFLD_DSI_VIDEO_BURST_MODE;

	return 0;
}