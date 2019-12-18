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
struct pm3_par {int /*<<< orphan*/  video; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int xres; unsigned int bits_per_pixel; int const yoffset; int sync; int vmode; int activate; int xres_virtual; scalar_t__ xoffset; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct pm3_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_NOW ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_MASK ; 
 int /*<<< orphan*/  PM3RD_CursorMode ; 
 int /*<<< orphan*/  PM3VideoControl_ENABLE ; 
 int /*<<< orphan*/  PM3VideoControl_HSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  PM3VideoControl_HSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  PM3VideoControl_LINE_DOUBLE_ON ; 
 int /*<<< orphan*/  PM3VideoControl_PIXELSIZE_16BIT ; 
 int /*<<< orphan*/  PM3VideoControl_PIXELSIZE_32BIT ; 
 int /*<<< orphan*/  PM3VideoControl_PIXELSIZE_8BIT ; 
 int /*<<< orphan*/  PM3VideoControl_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  PM3VideoControl_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  PM3_WRITE_DAC_REG (struct pm3_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm3fb_clear_colormap (struct pm3_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm3fb_init_engine (struct fb_info*) ; 
 int /*<<< orphan*/  pm3fb_shift_bpp (unsigned int const,scalar_t__) ; 
 int /*<<< orphan*/  pm3fb_write_mode (struct fb_info*) ; 

__attribute__((used)) static int pm3fb_set_par(struct fb_info *info)
{
	struct pm3_par *par = info->par;
	const u32 xres = (info->var.xres + 31) & ~31;
	const unsigned bpp = info->var.bits_per_pixel;

	par->base = pm3fb_shift_bpp(bpp, (info->var.yoffset * xres)
					+ info->var.xoffset);
	par->video = 0;

	if (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		par->video |= PM3VideoControl_HSYNC_ACTIVE_HIGH;
	else
		par->video |= PM3VideoControl_HSYNC_ACTIVE_LOW;

	if (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		par->video |= PM3VideoControl_VSYNC_ACTIVE_HIGH;
	else
		par->video |= PM3VideoControl_VSYNC_ACTIVE_LOW;

	if ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE)
		par->video |= PM3VideoControl_LINE_DOUBLE_ON;

	if ((info->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		par->video |= PM3VideoControl_ENABLE;
	else
		DPRINTK("PM3Video disabled\n");

	switch (bpp) {
	case 8:
		par->video |= PM3VideoControl_PIXELSIZE_8BIT;
		break;
	case 16:
		par->video |= PM3VideoControl_PIXELSIZE_16BIT;
		break;
	case 32:
		par->video |= PM3VideoControl_PIXELSIZE_32BIT;
		break;
	default:
		DPRINTK("Unsupported depth\n");
		break;
	}

	info->fix.visual =
		(bpp == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = ((info->var.xres_virtual + 7)  >> 3) * bpp;

/*	pm3fb_clear_memory(info, 0);*/
	pm3fb_clear_colormap(par, 0, 0, 0);
	PM3_WRITE_DAC_REG(par, PM3RD_CursorMode, 0);
	pm3fb_init_engine(info);
	pm3fb_write_mode(info);
	return 0;
}