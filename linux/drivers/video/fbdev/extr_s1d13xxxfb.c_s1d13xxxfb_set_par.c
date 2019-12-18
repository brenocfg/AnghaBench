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
struct s1d13xxxfb_par {int display; } ;
struct TYPE_4__ {int line_length; } ;
struct TYPE_3__ {int bits_per_pixel; int xres; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct s1d13xxxfb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S1DREG_CRT_DISP_MODE ; 
 int /*<<< orphan*/  S1DREG_LCD_DISP_MODE ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 unsigned int s1d13xxxfb_readreg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s1d13xxxfb_setup_pseudocolour (struct fb_info*) ; 
 int /*<<< orphan*/  s1d13xxxfb_setup_truecolour (struct fb_info*) ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
s1d13xxxfb_set_par(struct fb_info *info)
{
	struct s1d13xxxfb_par *s1dfb = info->par;
	unsigned int val;

	dbg("s1d13xxxfb_set_par: bpp=%d\n", info->var.bits_per_pixel);

	if ((s1dfb->display & 0x01))	/* LCD */
		val = s1d13xxxfb_readreg(s1dfb, S1DREG_LCD_DISP_MODE);   /* read colour control */
	else	/* CRT */
		val = s1d13xxxfb_readreg(s1dfb, S1DREG_CRT_DISP_MODE);   /* read colour control */

	val &= ~0x07;

	switch (info->var.bits_per_pixel) {
		case 4:
			dbg("pseudo colour 4\n");
			s1d13xxxfb_setup_pseudocolour(info);
			val |= 2;
			break;
		case 8:
			dbg("pseudo colour 8\n");
			s1d13xxxfb_setup_pseudocolour(info);
			val |= 3;
			break;
		case 16:
			dbg("true colour\n");
			s1d13xxxfb_setup_truecolour(info);
			val |= 5;
			break;

		default:
			dbg("bpp not supported!\n");
			return -EINVAL;
	}

	dbg("writing %02x to display mode register\n", val);

	if ((s1dfb->display & 0x01))	/* LCD */
		s1d13xxxfb_writereg(s1dfb, S1DREG_LCD_DISP_MODE, val);
	else	/* CRT */
		s1d13xxxfb_writereg(s1dfb, S1DREG_CRT_DISP_MODE, val);

	info->fix.line_length  = info->var.xres * info->var.bits_per_pixel;
	info->fix.line_length /= 8;

	dbg("setting line_length to %d\n", info->fix.line_length);

	dbg("done setup\n");

	return 0;
}