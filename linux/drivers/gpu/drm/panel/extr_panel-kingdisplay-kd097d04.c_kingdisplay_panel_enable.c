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
struct kingdisplay_panel {int enabled; int /*<<< orphan*/  backlight; } ;
struct drm_panel {TYPE_1__* drm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int backlight_enable (int /*<<< orphan*/ ) ; 
 struct kingdisplay_panel* to_kingdisplay_panel (struct drm_panel*) ; 

__attribute__((used)) static int kingdisplay_panel_enable(struct drm_panel *panel)
{
	struct kingdisplay_panel *kingdisplay = to_kingdisplay_panel(panel);
	int ret;

	if (kingdisplay->enabled)
		return 0;

	ret = backlight_enable(kingdisplay->backlight);
	if (ret) {
		DRM_DEV_ERROR(panel->drm->dev,
			      "Failed to enable backlight %d\n", ret);
		return ret;
	}

	kingdisplay->enabled = true;

	return 0;
}