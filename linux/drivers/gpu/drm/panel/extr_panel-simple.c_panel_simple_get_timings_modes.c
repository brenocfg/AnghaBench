#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct videomode {int dummy; } ;
struct TYPE_5__ {struct drm_device* drm; struct drm_connector* connector; } ;
struct panel_simple {TYPE_4__* desc; TYPE_1__ base; } ;
struct drm_display_mode {int /*<<< orphan*/  type; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  typ; } ;
struct TYPE_6__ {int /*<<< orphan*/  typ; } ;
struct display_timing {TYPE_3__ vactive; TYPE_2__ hactive; } ;
struct TYPE_8__ {unsigned int num_timings; struct display_timing* timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_display_mode_from_videomode (struct videomode*,struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_create (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing const*,struct videomode*) ; 

__attribute__((used)) static unsigned int panel_simple_get_timings_modes(struct panel_simple *panel)
{
	struct drm_connector *connector = panel->base.connector;
	struct drm_device *drm = panel->base.drm;
	struct drm_display_mode *mode;
	unsigned int i, num = 0;

	for (i = 0; i < panel->desc->num_timings; i++) {
		const struct display_timing *dt = &panel->desc->timings[i];
		struct videomode vm;

		videomode_from_timing(dt, &vm);
		mode = drm_mode_create(drm);
		if (!mode) {
			dev_err(drm->dev, "failed to add mode %ux%u\n",
				dt->hactive.typ, dt->vactive.typ);
			continue;
		}

		drm_display_mode_from_videomode(&vm, mode);

		mode->type |= DRM_MODE_TYPE_DRIVER;

		if (panel->desc->num_timings == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		num++;
	}

	return num;
}