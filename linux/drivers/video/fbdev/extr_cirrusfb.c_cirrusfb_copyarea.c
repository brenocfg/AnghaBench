#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  line_length; } ;
struct TYPE_3__ {int bits_per_pixel; scalar_t__ xres_virtual; scalar_t__ yres_virtual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_2__ fix; TYPE_1__ var; struct cirrusfb_info* par; } ;
struct fb_copyarea {scalar_t__ width; scalar_t__ height; scalar_t__ sx; scalar_t__ sy; scalar_t__ dx; scalar_t__ dy; } ;
struct cirrusfb_info {int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  cirrusfb_BitBLT (int /*<<< orphan*/ ,int,int,scalar_t__,int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fb_copyarea*,struct fb_copyarea const*,int) ; 

__attribute__((used)) static void cirrusfb_copyarea(struct fb_info *info,
			      const struct fb_copyarea *area)
{
	struct fb_copyarea modded;
	u32 vxres, vyres;
	struct cirrusfb_info *cinfo = info->par;
	int m = info->var.bits_per_pixel;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_copyarea(info, area);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;
	memcpy(&modded, area, sizeof(struct fb_copyarea));

	if (!modded.width || !modded.height ||
	   modded.sx >= vxres || modded.sy >= vyres ||
	   modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.sx + modded.width > vxres)
		modded.width = vxres - modded.sx;
	if (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	if (modded.sy + modded.height > vyres)
		modded.height = vyres - modded.sy;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	cirrusfb_BitBLT(cinfo->regbase, info->var.bits_per_pixel,
			(area->sx * m) / 8, area->sy,
			(area->dx * m) / 8, area->dy,
			(area->width * m) / 8, area->height,
			info->fix.line_length);

}