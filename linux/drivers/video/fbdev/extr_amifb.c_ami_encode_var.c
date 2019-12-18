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
typedef  size_t u_short ;
struct TYPE_4__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_3__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct fb_var_screeninfo {size_t xres; size_t yres; int bits_per_pixel; int height; int width; int vmode; size_t hsync_len; size_t right_margin; size_t left_margin; size_t vsync_len; size_t lower_margin; size_t upper_margin; int /*<<< orphan*/  sync; int /*<<< orphan*/  pixclock; scalar_t__ activate; scalar_t__ nonstd; TYPE_2__ transp; TYPE_1__ red; TYPE_1__ green; TYPE_1__ blue; scalar_t__ grayscale; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;
struct amifb_par {size_t clk_shift; size_t line_shift; size_t xres; size_t yres; int bpp; int bplcon0; int fmode; int beamcon0; size_t hsstop; size_t hsstrt; size_t htotal; size_t vsstop; size_t vsstrt; size_t vtotal; size_t diwstop_v; int vmode; int /*<<< orphan*/  diwstop_h; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; int /*<<< orphan*/  vyres; int /*<<< orphan*/  vxres; } ;

/* Variables and functions */
 int BMC0_CSYTRUE ; 
 int BMC0_HSYTRUE ; 
 int BMC0_VARBEAMEN ; 
 int BMC0_VSYTRUE ; 
 int BPC0_ERSY ; 
 int BPC0_HAM ; 
 int BPC0_LACE ; 
 scalar_t__ FB_NONSTD_HAM ; 
 int /*<<< orphan*/  FB_SYNC_BROADCAST ; 
 int /*<<< orphan*/  FB_SYNC_COMP_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_EXT ; 
 int /*<<< orphan*/  FB_SYNC_HOR_HIGH_ACT ; 
 int /*<<< orphan*/  FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_NONINTERLACED ; 
 int FB_VMODE_YWRAP ; 
 int FMODE_BSCAN2 ; 
 scalar_t__ IS_AGA ; 
 int /*<<< orphan*/  IS_OCS ; 
 size_t down4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 size_t mod4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pixclock ; 

__attribute__((used)) static void ami_encode_var(struct fb_var_screeninfo *var,
			   struct amifb_par *par)
{
	u_short clk_shift, line_shift;

	memset(var, 0, sizeof(struct fb_var_screeninfo));

	clk_shift = par->clk_shift;
	line_shift = par->line_shift;

	var->xres = par->xres;
	var->yres = par->yres;
	var->xres_virtual = par->vxres;
	var->yres_virtual = par->vyres;
	var->xoffset = par->xoffset;
	var->yoffset = par->yoffset;

	var->bits_per_pixel = par->bpp;
	var->grayscale = 0;

	var->red.offset = 0;
	var->red.msb_right = 0;
	var->red.length = par->bpp;
	if (par->bplcon0 & BPC0_HAM)
		var->red.length -= 2;
	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;

	if (par->bplcon0 & BPC0_HAM)
		var->nonstd = FB_NONSTD_HAM;
	else
		var->nonstd = 0;
	var->activate = 0;

	var->height = -1;
	var->width = -1;

	var->pixclock = pixclock[clk_shift];

	if (IS_AGA && par->fmode & FMODE_BSCAN2)
		var->vmode = FB_VMODE_DOUBLE;
	else if (par->bplcon0 & BPC0_LACE)
		var->vmode = FB_VMODE_INTERLACED;
	else
		var->vmode = FB_VMODE_NONINTERLACED;

	if (!IS_OCS && par->beamcon0 & BMC0_VARBEAMEN) {
		var->hsync_len = (par->hsstop - par->hsstrt)>>clk_shift;
		var->right_margin = par->hsstrt>>clk_shift;
		var->left_margin = (par->htotal>>clk_shift) - var->xres - var->right_margin - var->hsync_len;
		var->vsync_len = (par->vsstop - par->vsstrt)>>line_shift;
		var->lower_margin = par->vsstrt>>line_shift;
		var->upper_margin = (par->vtotal>>line_shift) - var->yres - var->lower_margin - var->vsync_len;
		var->sync = 0;
		if (par->beamcon0 & BMC0_HSYTRUE)
			var->sync |= FB_SYNC_HOR_HIGH_ACT;
		if (par->beamcon0 & BMC0_VSYTRUE)
			var->sync |= FB_SYNC_VERT_HIGH_ACT;
		if (par->beamcon0 & BMC0_CSYTRUE)
			var->sync |= FB_SYNC_COMP_HIGH_ACT;
	} else {
		var->sync = FB_SYNC_BROADCAST;
		var->hsync_len = (152>>clk_shift) + mod4(par->diwstop_h);
		var->right_margin = ((par->htotal - down4(par->diwstop_h))>>clk_shift) + var->hsync_len;
		var->left_margin = (par->htotal>>clk_shift) - var->xres - var->right_margin - var->hsync_len;
		var->vsync_len = 4>>line_shift;
		var->lower_margin = ((par->vtotal - par->diwstop_v)>>line_shift) + var->vsync_len;
		var->upper_margin = (((par->vtotal - 2)>>line_shift) + 1) - var->yres -
				    var->lower_margin - var->vsync_len;
	}

	if (par->bplcon0 & BPC0_ERSY)
		var->sync |= FB_SYNC_EXT;
	if (par->vmode & FB_VMODE_YWRAP)
		var->vmode |= FB_VMODE_YWRAP;
}