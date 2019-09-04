#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct panel_lvds {scalar_t__ data_mirror; int /*<<< orphan*/  bus_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  video_mode; TYPE_1__ panel; } ;
struct drm_panel {int dummy; } ;
struct drm_display_mode {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_2__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_BUS_FLAG_DATA_LSB_TO_MSB ; 
 int /*<<< orphan*/  DRM_BUS_FLAG_DATA_MSB_TO_LSB ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  drm_display_info_set_bus_formats (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_display_mode_from_videomode (int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct panel_lvds* to_panel_lvds (struct drm_panel*) ; 

__attribute__((used)) static int panel_lvds_get_modes(struct drm_panel *panel)
{
	struct panel_lvds *lvds = to_panel_lvds(panel);
	struct drm_connector *connector = lvds->panel.connector;
	struct drm_display_mode *mode;

	mode = drm_mode_create(lvds->panel.drm);
	if (!mode)
		return 0;

	drm_display_mode_from_videomode(&lvds->video_mode, mode);
	mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = lvds->width;
	connector->display_info.height_mm = lvds->height;
	drm_display_info_set_bus_formats(&connector->display_info,
					 &lvds->bus_format, 1);
	connector->display_info.bus_flags = lvds->data_mirror
					  ? DRM_BUS_FLAG_DATA_LSB_TO_MSB
					  : DRM_BUS_FLAG_DATA_MSB_TO_LSB;

	return 1;
}