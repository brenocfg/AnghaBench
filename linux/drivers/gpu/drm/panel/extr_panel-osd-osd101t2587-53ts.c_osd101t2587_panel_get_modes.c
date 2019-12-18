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
struct osd101t2587_panel {TYPE_4__* default_mode; } ;
struct drm_panel {TYPE_2__* connector; TYPE_3__* drm; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int width_mm; int height_mm; } ;
struct TYPE_6__ {TYPE_1__ display_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_display_mode* drm_mode_duplicate (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (TYPE_2__*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 struct osd101t2587_panel* ti_osd_panel (struct drm_panel*) ; 

__attribute__((used)) static int osd101t2587_panel_get_modes(struct drm_panel *panel)
{
	struct osd101t2587_panel *osd101t2587 = ti_osd_panel(panel);
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(panel->drm, osd101t2587->default_mode);
	if (!mode) {
		dev_err(panel->drm->dev, "failed to add mode %ux%ux@%u\n",
			osd101t2587->default_mode->hdisplay,
			osd101t2587->default_mode->vdisplay,
			osd101t2587->default_mode->vrefresh);
		return -ENOMEM;
	}

	drm_mode_set_name(mode);

	drm_mode_probed_add(panel->connector, mode);

	panel->connector->display_info.width_mm = 217;
	panel->connector->display_info.height_mm = 136;

	return 1;
}