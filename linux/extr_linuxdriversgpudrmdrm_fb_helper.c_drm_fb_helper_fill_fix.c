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
typedef  int uint32_t ;
struct TYPE_2__ {int xpanstep; int ypanstep; int line_length; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ type_aux; scalar_t__ mmio_len; scalar_t__ mmio_start; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 

void drm_fb_helper_fill_fix(struct fb_info *info, uint32_t pitch,
			    uint32_t depth)
{
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = depth == 8 ? FB_VISUAL_PSEUDOCOLOR :
		FB_VISUAL_TRUECOLOR;
	info->fix.mmio_start = 0;
	info->fix.mmio_len = 0;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 1; /* doing it in hw */
	info->fix.ypanstep = 1; /* doing it in hw */
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;

	info->fix.line_length = pitch;
}