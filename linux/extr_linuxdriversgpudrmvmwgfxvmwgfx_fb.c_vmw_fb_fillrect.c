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
struct fb_info {int /*<<< orphan*/  par; } ;
struct fb_fillrect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  vmw_fb_dirty_mark (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_fb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	cfb_fillrect(info, rect);
	vmw_fb_dirty_mark(info->par, rect->dx, rect->dy,
			  rect->width, rect->height);
}