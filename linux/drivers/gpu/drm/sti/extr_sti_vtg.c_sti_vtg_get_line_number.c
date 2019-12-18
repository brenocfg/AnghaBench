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
struct drm_display_mode {int vtotal; int vsync_start; int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 

u32 sti_vtg_get_line_number(struct drm_display_mode mode, int y)
{
	u32 start_line = mode.vtotal - mode.vsync_start + 1;

	if (mode.flags & DRM_MODE_FLAG_INTERLACE)
		start_line *= 2;

	return start_line + y;
}