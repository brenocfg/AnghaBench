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
struct fb_info {int dummy; } ;
struct fb_fillrect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_dirty (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

void drm_fb_helper_sys_fillrect(struct fb_info *info,
				const struct fb_fillrect *rect)
{
	sys_fillrect(info, rect);
	drm_fb_helper_dirty(info, rect->dx, rect->dy,
			    rect->width, rect->height);
}