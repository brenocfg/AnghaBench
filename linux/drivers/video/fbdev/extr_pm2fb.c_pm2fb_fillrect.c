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
typedef  int u32 ;
struct pm2fb_par {int dummy; } ;
struct TYPE_4__ {int xres_virtual; int yres_virtual; int bits_per_pixel; } ;
struct TYPE_3__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ state; int flags; TYPE_2__ var; scalar_t__ pseudo_palette; TYPE_1__ fix; struct pm2fb_par* par; } ;
struct fb_fillrect {size_t color; scalar_t__ rop; int width; int height; int dx; int dy; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int PM2F_CONFIG_FB_WRITE_ENABLE ; 
 int PM2F_INCREASE_X ; 
 int PM2F_INCREASE_Y ; 
 int PM2F_RENDER_FASTFILL ; 
 int PM2F_RENDER_RECTANGLE ; 
 int /*<<< orphan*/  PM2R_COLOR_DDA_MODE ; 
 int /*<<< orphan*/  PM2R_CONFIG ; 
 int /*<<< orphan*/  PM2R_CONSTANT_COLOR ; 
 int /*<<< orphan*/  PM2R_FB_BLOCK_COLOR ; 
 int /*<<< orphan*/  PM2R_RECTANGLE_ORIGIN ; 
 int /*<<< orphan*/  PM2R_RECTANGLE_SIZE ; 
 int /*<<< orphan*/  PM2R_RENDER ; 
 scalar_t__ ROP_COPY ; 
 int /*<<< orphan*/  WAIT_FIFO (struct pm2fb_par*,int) ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  memcpy (struct fb_fillrect*,struct fb_fillrect const*,int) ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void pm2fb_fillrect(struct fb_info *info,
				const struct fb_fillrect *region)
{
	struct pm2fb_par *par = info->par;
	struct fb_fillrect modded;
	int vxres, vyres;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		((u32 *)info->pseudo_palette)[region->color] : region->color;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	if ((info->flags & FBINFO_HWACCEL_DISABLED) ||
		region->rop != ROP_COPY ) {
		cfb_fillrect(info, region);
		return;
	}

	vxres = info->var.xres_virtual;
	vyres = info->var.yres_virtual;

	memcpy(&modded, region, sizeof(struct fb_fillrect));

	if (!modded.width || !modded.height ||
	    modded.dx >= vxres || modded.dy >= vyres)
		return;

	if (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	if (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	if (info->var.bits_per_pixel == 8)
		color |= color << 8;
	if (info->var.bits_per_pixel <= 16)
		color |= color << 16;

	WAIT_FIFO(par, 3);
	pm2_WR(par, PM2R_CONFIG, PM2F_CONFIG_FB_WRITE_ENABLE);
	pm2_WR(par, PM2R_RECTANGLE_ORIGIN, (modded.dy << 16) | modded.dx);
	pm2_WR(par, PM2R_RECTANGLE_SIZE, (modded.height << 16) | modded.width);
	if (info->var.bits_per_pixel != 24) {
		WAIT_FIFO(par, 2);
		pm2_WR(par, PM2R_FB_BLOCK_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE | PM2F_RENDER_FASTFILL);
	} else {
		WAIT_FIFO(par, 4);
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 1);
		pm2_WR(par, PM2R_CONSTANT_COLOR, color);
		wmb();
		pm2_WR(par, PM2R_RENDER,
				PM2F_RENDER_RECTANGLE |
				PM2F_INCREASE_X | PM2F_INCREASE_Y );
		pm2_WR(par, PM2R_COLOR_DDA_MODE, 0);
	}
}