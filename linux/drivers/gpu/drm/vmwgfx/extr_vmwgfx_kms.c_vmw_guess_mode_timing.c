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
typedef  int u32 ;
struct drm_display_mode {int clock; int /*<<< orphan*/  vrefresh; scalar_t__ vtotal; scalar_t__ htotal; scalar_t__ vsync_end; scalar_t__ vsync_start; scalar_t__ vdisplay; scalar_t__ hsync_end; scalar_t__ hsync_start; scalar_t__ hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 

void vmw_guess_mode_timing(struct drm_display_mode *mode)
{
	mode->hsync_start = mode->hdisplay + 50;
	mode->hsync_end = mode->hsync_start + 50;
	mode->htotal = mode->hsync_end + 50;

	mode->vsync_start = mode->vdisplay + 50;
	mode->vsync_end = mode->vsync_start + 50;
	mode->vtotal = mode->vsync_end + 50;

	mode->clock = (u32)mode->htotal * (u32)mode->vtotal / 100 * 6;
	mode->vrefresh = drm_mode_vrefresh(mode);
}