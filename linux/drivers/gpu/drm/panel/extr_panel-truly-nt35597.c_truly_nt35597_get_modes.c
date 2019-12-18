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
struct truly_nt35597 {int /*<<< orphan*/  dev; struct nt35597_config* config; } ;
struct nt35597_config {int /*<<< orphan*/  dm; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_panel {struct drm_connector* connector; } ;
struct drm_display_mode {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct truly_nt35597* panel_to_ctx (struct drm_panel*) ; 

__attribute__((used)) static int truly_nt35597_get_modes(struct drm_panel *panel)
{
	struct drm_connector *connector = panel->connector;
	struct truly_nt35597 *ctx = panel_to_ctx(panel);
	struct drm_display_mode *mode;
	const struct nt35597_config *config;

	config = ctx->config;
	mode = drm_mode_create(connector->dev);
	if (!mode) {
		DRM_DEV_ERROR(ctx->dev,
			"failed to create a new display mode\n");
		return 0;
	}

	connector->display_info.width_mm = config->width_mm;
	connector->display_info.height_mm = config->height_mm;
	drm_mode_copy(mode, config->dm);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	return 1;
}