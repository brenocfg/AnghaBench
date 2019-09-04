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
struct mdfld_dsi_connector {int dummy; } ;
struct mdfld_dsi_config {struct drm_display_mode* fixed_mode; } ;
struct drm_display_mode {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct mdfld_dsi_connector* mdfld_dsi_connector (struct drm_connector*) ; 
 struct mdfld_dsi_config* mdfld_dsi_get_config (struct mdfld_dsi_connector*) ; 

__attribute__((used)) static int mdfld_dsi_connector_get_modes(struct drm_connector *connector)
{
	struct mdfld_dsi_connector *dsi_connector =
				mdfld_dsi_connector(connector);
	struct mdfld_dsi_config *dsi_config =
				mdfld_dsi_get_config(dsi_connector);
	struct drm_display_mode *fixed_mode = dsi_config->fixed_mode;
	struct drm_display_mode *dup_mode = NULL;
	struct drm_device *dev = connector->dev;

	if (fixed_mode) {
		dev_dbg(dev->dev, "fixed_mode %dx%d\n",
				fixed_mode->hdisplay, fixed_mode->vdisplay);
		dup_mode = drm_mode_duplicate(dev, fixed_mode);
		drm_mode_probed_add(connector, dup_mode);
		return 1;
	}
	DRM_ERROR("Didn't get any modes!\n");
	return 0;
}