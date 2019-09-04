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
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  drm_fb_helper_dirty (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drm_fb_helper_cfb_copyarea(struct fb_info *info,
				const struct fb_copyarea *area)
{
	cfb_copyarea(info, area);
	drm_fb_helper_dirty(info, area->dx, area->dy,
			    area->width, area->height);
}