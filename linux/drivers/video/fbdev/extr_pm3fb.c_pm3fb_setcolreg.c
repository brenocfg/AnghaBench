#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct pm3_par {int dummy; } ;
struct TYPE_12__ {scalar_t__ visual; } ;
struct TYPE_10__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_7__ {unsigned int offset; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; scalar_t__ grayscale; } ;
struct fb_info {TYPE_6__ fix; scalar_t__ pseudo_palette; TYPE_5__ var; struct pm3_par* par; } ;

/* Variables and functions */
 unsigned int CNVT_TOHW (unsigned int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  pm3fb_set_color (struct pm3_par*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int pm3fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	struct pm3_par *par = info->par;

	if (regno >= 256)  /* no. of hw registers */
	   return -EINVAL;

	/* grayscale works only partially under directcolor */
	/* grayscale = 0.30*R + 0.59*G + 0.11*B */
	if (info->var.grayscale)
	   red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;

	/* Directcolor:
	 *   var->{color}.offset contains start of bitfield
	 *   var->{color}.length contains length of bitfield
	 *   {hardwarespecific} contains width of DAC
	 *   pseudo_palette[X] is programmed to (X << red.offset) |
	 *					(X << green.offset) |
	 *					(X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *   color depth = SUM(var->{color}.length)
	 *
	 * Pseudocolor:
	 *	var->{color}.offset is 0
	 *	var->{color}.length contains width of DAC or the number
	 *			of unique colors available (color depth)
	 *	pseudo_palette is not used
	 *	RAMDAC[X] is programmed to (red, green, blue)
	 *	color depth = var->{color}.length
	 */

	/*
	 * This is the point where the color is converted to something that
	 * is acceptable by the hardware.
	 */
#define CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)
	red = CNVT_TOHW(red, info->var.red.length);
	green = CNVT_TOHW(green, info->var.green.length);
	blue = CNVT_TOHW(blue, info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);
#undef CNVT_TOHW

	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
		u32 v;

		if (regno >= 16)
			return -EINVAL;

		v = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);

		switch (info->var.bits_per_pixel) {
		case 8:
			break;
		case 16:
		case 32:
			((u32 *)(info->pseudo_palette))[regno] = v;
			break;
		}
		return 0;
	} else if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		pm3fb_set_color(par, regno, red, green, blue);

	return 0;
}