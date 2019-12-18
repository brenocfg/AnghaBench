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
struct pm2fb_par {unsigned int* palette; } ;
struct TYPE_14__ {int visual; } ;
struct TYPE_12__ {int length; unsigned int offset; } ;
struct TYPE_11__ {int length; unsigned int offset; } ;
struct TYPE_10__ {int length; unsigned int offset; } ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_13__ {int bits_per_pixel; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; scalar_t__ grayscale; } ;
struct TYPE_8__ {unsigned int len; } ;
struct fb_info {TYPE_7__ fix; TYPE_6__ var; TYPE_1__ cmap; struct pm2fb_par* par; } ;

/* Variables and functions */
 unsigned int CNVT_TOHW (unsigned int,int) ; 
 int EINVAL ; 
#define  FB_VISUAL_DIRECTCOLOR 130 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int /*<<< orphan*/  set_color (struct pm2fb_par*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int pm2fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	struct pm2fb_par *par = info->par;

	if (regno >= info->cmap.len)  /* no. of hw registers */
		return -EINVAL;
	/*
	 * Program hardware... do anything you want with transp
	 */

	/* grayscale works only partially under directcolor */
	/* grayscale = 0.30*R + 0.59*G + 0.11*B */
	if (info->var.grayscale)
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;

	/* Directcolor:
	 *   var->{color}.offset contains start of bitfield
	 *   var->{color}.length contains length of bitfield
	 *   {hardwarespecific} contains width of DAC
	 *   cmap[X] is programmed to
	 *   (X << red.offset) | (X << green.offset) | (X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Pseudocolor:
	 *    uses offset = 0 && length = DAC register width.
	 *    var->{color}.offset is 0
	 *    var->{color}.length contains width of DAC
	 *    cmap is not used
	 *    DAC[X] is programmed to (red, green, blue)
	 * Truecolor:
	 *    does not use RAMDAC (usually has 3 of them).
	 *    var->{color}.offset contains start of bitfield
	 *    var->{color}.length contains length of bitfield
	 *    cmap is programmed to
	 *    (red << red.offset) | (green << green.offset) |
	 *    (blue << blue.offset) | (transp << transp.offset)
	 *    RAMDAC does not exist
	 */
#define CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF -(val)) >> 16)
	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		transp = CNVT_TOHW(transp, info->var.transp.length);
		break;
	case FB_VISUAL_DIRECTCOLOR:
		/* example here assumes 8 bit DAC. Might be different
		 * for your hardware */
		red = CNVT_TOHW(red, 8);
		green = CNVT_TOHW(green, 8);
		blue = CNVT_TOHW(blue, 8);
		/* hey, there is bug in transp handling... */
		transp = CNVT_TOHW(transp, 8);
		break;
	}
#undef CNVT_TOHW
	/* Truecolor has hardware independent palette */
	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
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
		case 24:
		case 32:
			par->palette[regno] = v;
			break;
		}
		return 0;
	} else if (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		set_color(par, regno, red, green, blue);

	return 0;
}