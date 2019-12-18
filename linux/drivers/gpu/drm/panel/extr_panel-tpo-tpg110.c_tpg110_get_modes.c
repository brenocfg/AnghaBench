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
struct tpg110 {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* panel_mode; } ;
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_display_mode {int type; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  bus_flags; } ;

/* Variables and functions */
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 struct tpg110* to_tpg110 (struct drm_panel*) ; 

__attribute__((used)) static int tpg110_get_modes(struct drm_panel *panel)
{
	struct drm_connector *connector = panel->connector;
	struct tpg110 *tpg = to_tpg110(panel);
	struct drm_display_mode *mode;

	connector->display_info.width_mm = tpg->width;
	connector->display_info.height_mm = tpg->height;
	connector->display_info.bus_flags = tpg->panel_mode->bus_flags;

	mode = drm_mode_duplicate(panel->drm, &tpg->panel_mode->mode);
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	mode->width_mm = tpg->width;
	mode->height_mm = tpg->height;

	drm_mode_probed_add(connector, mode);

	return 1;
}