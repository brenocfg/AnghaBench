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
typedef  int u32 ;
struct nvidia_par {scalar_t__ lockup; } ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ state; scalar_t__ pseudo_palette; TYPE_1__ var; struct nvidia_par* par; } ;
struct fb_fillrect {int color; scalar_t__ rop; int dx; int dy; int width; int height; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  NVDmaKickoff (struct nvidia_par*) ; 
 int /*<<< orphan*/  NVDmaNext (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVDmaStart (struct fb_info*,struct nvidia_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVSetRopSolid (struct fb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECT_SOLID_COLOR ; 
 int /*<<< orphan*/  RECT_SOLID_RECTS (int /*<<< orphan*/ ) ; 
 scalar_t__ ROP_COPY ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

void nvidiafb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct nvidia_par *par = info->par;
	u32 color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;

	if (par->lockup) {
		cfb_fillrect(info, rect);
		return;
	}

	if (info->var.bits_per_pixel == 8)
		color = rect->color;
	else
		color = ((u32 *) info->pseudo_palette)[rect->color];

	if (rect->rop != ROP_COPY)
		NVSetRopSolid(info, rect->rop, ~0);

	NVDmaStart(info, par, RECT_SOLID_COLOR, 1);
	NVDmaNext(par, color);

	NVDmaStart(info, par, RECT_SOLID_RECTS(0), 2);
	NVDmaNext(par, (rect->dx << 16) | rect->dy);
	NVDmaNext(par, (rect->width << 16) | rect->height);

	NVDmaKickoff(par);

	if (rect->rop != ROP_COPY)
		NVSetRopSolid(info, ROP_COPY, ~0);
}