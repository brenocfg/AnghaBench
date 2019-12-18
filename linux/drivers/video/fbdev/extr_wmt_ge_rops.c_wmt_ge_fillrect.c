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
typedef  unsigned long u32 ;
struct TYPE_6__ {int bits_per_pixel; int xres_virtual; int yres_virtual; } ;
struct TYPE_5__ {scalar_t__ visual; int smem_start; } ;
struct fb_info {scalar_t__ state; TYPE_3__ var; TYPE_2__ fix; TYPE_1__* fbops; scalar_t__ pseudo_palette; } ;
struct fb_fillrect {size_t color; int dx; int dy; int width; int height; scalar_t__ rop; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_sync ) (struct fb_info*) ;} ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 scalar_t__ GE_COMMAND_OFF ; 
 scalar_t__ GE_DEPTH_OFF ; 
 scalar_t__ GE_DESTAREAH_OFF ; 
 scalar_t__ GE_DESTAREAW_OFF ; 
 scalar_t__ GE_DESTAREAX_OFF ; 
 scalar_t__ GE_DESTAREAY_OFF ; 
 scalar_t__ GE_DESTBASE_OFF ; 
 scalar_t__ GE_DESTDISPH_OFF ; 
 scalar_t__ GE_DESTDISPW_OFF ; 
 scalar_t__ GE_FIRE_OFF ; 
 scalar_t__ GE_HIGHCOLOR_OFF ; 
 scalar_t__ GE_PAT0C_OFF ; 
 scalar_t__ GE_ROPCODE_OFF ; 
 scalar_t__ ROP_XOR ; 
 unsigned long pixel_to_pat (int,unsigned long) ; 
 scalar_t__ regbase ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void wmt_ge_fillrect(struct fb_info *p, const struct fb_fillrect *rect)
{
	unsigned long fg, pat;

	if (p->state != FBINFO_STATE_RUNNING)
		return;

	if (p->fix.visual == FB_VISUAL_TRUECOLOR ||
	    p->fix.visual == FB_VISUAL_DIRECTCOLOR)
		fg = ((u32 *) (p->pseudo_palette))[rect->color];
	else
		fg = rect->color;

	pat = pixel_to_pat(p->var.bits_per_pixel, fg);

	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	writel(p->var.bits_per_pixel == 32 ? 3 :
	      (p->var.bits_per_pixel == 8 ? 0 : 1), regbase + GE_DEPTH_OFF);
	writel(p->var.bits_per_pixel == 15 ? 1 : 0, regbase + GE_HIGHCOLOR_OFF);
	writel(p->fix.smem_start, regbase + GE_DESTBASE_OFF);
	writel(p->var.xres_virtual - 1, regbase + GE_DESTDISPW_OFF);
	writel(p->var.yres_virtual - 1, regbase + GE_DESTDISPH_OFF);
	writel(rect->dx, regbase + GE_DESTAREAX_OFF);
	writel(rect->dy, regbase + GE_DESTAREAY_OFF);
	writel(rect->width - 1, regbase + GE_DESTAREAW_OFF);
	writel(rect->height - 1, regbase + GE_DESTAREAH_OFF);

	writel(pat, regbase + GE_PAT0C_OFF);
	writel(1, regbase + GE_COMMAND_OFF);
	writel(rect->rop == ROP_XOR ? 0x5a : 0xf0, regbase + GE_ROPCODE_OFF);
	writel(1, regbase + GE_FIRE_OFF);
}