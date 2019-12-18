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
struct radeonfb_info {int dummy; } ;
struct TYPE_2__ {int xres_virtual; int yres_virtual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_1__ var; struct radeonfb_info* par; } ;
struct fb_fillrect {int width; int height; int dx; int dy; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  memcpy (struct fb_fillrect*,struct fb_fillrect const*,int) ; 
 int /*<<< orphan*/  radeon_fixup_offset (struct radeonfb_info*) ; 
 int /*<<< orphan*/  radeonfb_prim_fillrect (struct radeonfb_info*,struct fb_fillrect*) ; 

void radeonfb_fillrect(struct fb_info *info, const struct fb_fillrect *region)
{
	struct radeonfb_info *rinfo = info->par;
	struct fb_fillrect modded;
	int vxres, vyres;
  
	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if (info->flags & FBINFO_HWACCEL_DISABLED) {
		cfb_fillrect(info, region);
		return;
	}

	radeon_fixup_offset(rinfo);

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	memcpy(&modded, region, sizeof(struct fb_fillrect));

	if(!modded.width || !modded.height ||
	   modded.dx >= vxres || modded.dy >= vyres)
		return;
  
	if(modded.dx + modded.width  > vxres) modded.width  = vxres - modded.dx;
	if(modded.dy + modded.height > vyres) modded.height = vyres - modded.dy;

	radeonfb_prim_fillrect(rinfo, &modded);
}