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
struct drm_display_mode {int htotal; int hdisplay; int hsync_end; int hsync_start; int vsync_start; int vdisplay; } ;

/* Variables and functions */

__attribute__((used)) static bool
mode_is_rb(const struct drm_display_mode *mode)
{
	return (mode->htotal - mode->hdisplay == 160) &&
	       (mode->hsync_end - mode->hdisplay == 80) &&
	       (mode->hsync_end - mode->hsync_start == 32) &&
	       (mode->vsync_start - mode->vdisplay == 3);
}