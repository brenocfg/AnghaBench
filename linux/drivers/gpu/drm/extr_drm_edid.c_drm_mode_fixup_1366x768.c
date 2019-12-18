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
struct drm_display_mode {int hdisplay; int vdisplay; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 

void drm_mode_fixup_1366x768(struct drm_display_mode *mode)
{
	if (mode->hdisplay == 1368 && mode->vdisplay == 768) {
		mode->hdisplay = 1366;
		mode->hsync_start--;
		mode->hsync_end--;
		drm_mode_set_name(mode);
	}
}