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
struct fb_info {struct cirrus_fbdev* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct cirrus_fbdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_dirty_update (struct cirrus_fbdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_sys_copyarea (struct fb_info*,struct fb_copyarea const*) ; 

__attribute__((used)) static void cirrus_copyarea(struct fb_info *info,
			 const struct fb_copyarea *area)
{
	struct cirrus_fbdev *afbdev = info->par;
	drm_fb_helper_sys_copyarea(info, area);
	cirrus_dirty_update(afbdev, area->dx, area->dy, area->width,
			 area->height);
}