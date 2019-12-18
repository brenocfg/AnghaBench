#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nt39016_panel_info {int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  bus_format; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  display_mode; } ;
struct nt39016 {struct nt39016_panel_info* panel_info; } ;
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_display_mode {int type; } ;
struct TYPE_2__ {int bpc; int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  drm_display_info_set_bus_formats (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 struct nt39016* to_nt39016 (struct drm_panel*) ; 

__attribute__((used)) static int nt39016_get_modes(struct drm_panel *drm_panel)
{
	struct nt39016 *panel = to_nt39016(drm_panel);
	const struct nt39016_panel_info *panel_info = panel->panel_info;
	struct drm_connector *connector = drm_panel->connector;
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(drm_panel->drm, &panel_info->display_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.bpc = 8;
	connector->display_info.width_mm = panel_info->width_mm;
	connector->display_info.height_mm = panel_info->height_mm;

	drm_display_info_set_bus_formats(&connector->display_info,
					 &panel_info->bus_format, 1);
	connector->display_info.bus_flags = panel_info->bus_flags;

	return 1;
}