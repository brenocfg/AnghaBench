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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; scalar_t__ grayscale; } ;
struct TYPE_3__ {scalar_t__ visual; } ;
struct fb_info {TYPE_2__ var; int /*<<< orphan*/ * pseudo_palette; TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  chan_to_field (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lx_set_palette_reg (struct fb_info*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int lxfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}

	/* Truecolor has hardware independent palette */
	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 *pal = info->pseudo_palette;
		u32 v;

		if (regno >= 16)
			return -EINVAL;

		v  = chan_to_field(red, &info->var.red);
		v |= chan_to_field(green, &info->var.green);
		v |= chan_to_field(blue, &info->var.blue);

		pal[regno] = v;
	} else {
		if (regno >= 256)
			return -EINVAL;

		lx_set_palette_reg(info, regno, red, green, blue);
	}

	return 0;
}