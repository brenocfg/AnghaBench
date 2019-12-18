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
struct drm_display_mode {int vsync_start; int vdisplay; int vsync_end; int vtotal; int clock; } ;

/* Variables and functions */

__attribute__((used)) static void intel_tv_scale_mode_vert(struct drm_display_mode *mode,
				     int vdisplay, int top_margin,
				     int bottom_margin)
{
	int vsync_start = mode->vsync_start - mode->vdisplay + bottom_margin;
	int vsync_end = mode->vsync_end - mode->vdisplay + bottom_margin;
	int new_vtotal = mode->vtotal * vdisplay /
		(mode->vdisplay - top_margin - bottom_margin);

	mode->clock = mode->clock * new_vtotal / mode->vtotal;

	mode->vdisplay = vdisplay;
	mode->vsync_start = vdisplay + vsync_start * new_vtotal / mode->vtotal;
	mode->vsync_end = vdisplay + vsync_end * new_vtotal / mode->vtotal;
	mode->vtotal = new_vtotal;
}