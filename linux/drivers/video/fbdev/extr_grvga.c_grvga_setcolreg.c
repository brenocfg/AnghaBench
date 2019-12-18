#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct grvga_par {TYPE_1__* regs; } ;
struct TYPE_13__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_12__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_14__ {TYPE_6__ transp; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; scalar_t__ grayscale; } ;
struct TYPE_9__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_7__ var; TYPE_2__ fix; struct grvga_par* par; } ;
struct TYPE_8__ {int /*<<< orphan*/  clut; } ;

/* Variables and functions */
 unsigned int CNVT_TOHW (unsigned int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grvga_setcolreg(unsigned regno, unsigned red, unsigned green, unsigned blue, unsigned transp, struct fb_info *info)
{
	struct grvga_par *par;
	par = info->par;

	if (regno >= 256)	/* Size of CLUT */
		return -EINVAL;

	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}



#define CNVT_TOHW(val, width) ((((val)<<(width))+0x7FFF-(val))>>16)

	red    = CNVT_TOHW(red,   info->var.red.length);
	green  = CNVT_TOHW(green, info->var.green.length);
	blue   = CNVT_TOHW(blue,  info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);

#undef CNVT_TOHW

	/* In PSEUDOCOLOR we use the hardware CLUT */
	if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		__raw_writel((regno << 24) | (red << 16) | (green << 8) | blue,
			     &par->regs->clut);

	/* Truecolor uses the pseudo palette */
	else if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 v;
		if (regno >= 16)
			return -EINVAL;


		v =     (red    << info->var.red.offset)   |
			(green  << info->var.green.offset) |
			(blue   << info->var.blue.offset)  |
			(transp << info->var.transp.offset);

		((u32 *) (info->pseudo_palette))[regno] = v;
	}
	return 0;
}