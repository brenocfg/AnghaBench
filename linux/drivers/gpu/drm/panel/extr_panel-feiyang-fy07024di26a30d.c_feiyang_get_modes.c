#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct feiyang {TYPE_1__* dsi; } ;
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 TYPE_2__ feiyang_default_mode ; 
 struct feiyang* panel_to_feiyang (struct drm_panel*) ; 

__attribute__((used)) static int feiyang_get_modes(struct drm_panel *panel)
{
	struct drm_connector *connector = panel->connector;
	struct feiyang *ctx = panel_to_feiyang(panel);
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(panel->drm, &feiyang_default_mode);
	if (!mode) {
		DRM_DEV_ERROR(&ctx->dsi->dev, "failed to add mode %ux%ux@%u\n",
			      feiyang_default_mode.hdisplay,
			      feiyang_default_mode.vdisplay,
			      feiyang_default_mode.vrefresh);
		return -ENOMEM;
	}

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	return 1;
}