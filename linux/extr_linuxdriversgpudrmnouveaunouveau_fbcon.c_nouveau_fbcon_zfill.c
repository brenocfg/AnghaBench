#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct fb_info* fbdev; } ;
struct nouveau_fbdev {TYPE_2__ helper; } ;
struct TYPE_6__ {int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;
struct fb_info {TYPE_1__* fbops; TYPE_3__ var; } ;
struct fb_fillrect {int /*<<< orphan*/  rop; scalar_t__ color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ dy; scalar_t__ dx; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_fillrect ) (struct fb_info*,struct fb_fillrect*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_fillrect*) ; 

__attribute__((used)) static void
nouveau_fbcon_zfill(struct drm_device *dev, struct nouveau_fbdev *fbcon)
{
	struct fb_info *info = fbcon->helper.fbdev;
	struct fb_fillrect rect;

	/* Clear the entire fbcon.  The drm will program every connector
	 * with it's preferred mode.  If the sizes differ, one display will
	 * quite likely have garbage around the console.
	 */
	rect.dx = rect.dy = 0;
	rect.width = info->var.xres_virtual;
	rect.height = info->var.yres_virtual;
	rect.color = 0;
	rect.rop = ROP_COPY;
	info->fbops->fb_fillrect(info, &rect);
}