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
struct mga_fbdev {int dummy; } ;
struct fb_info {struct mga_fbdev* par; } ;
struct fb_fillrect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  mga_dirty_update (struct mga_fbdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mga_fillrect(struct fb_info *info,
			 const struct fb_fillrect *rect)
{
	struct mga_fbdev *mfbdev = info->par;
	drm_fb_helper_sys_fillrect(info, rect);
	mga_dirty_update(mfbdev, rect->dx, rect->dy, rect->width,
			 rect->height);
}