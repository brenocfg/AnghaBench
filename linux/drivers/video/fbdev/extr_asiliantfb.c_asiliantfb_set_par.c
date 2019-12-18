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
typedef  int u8 ;
struct TYPE_4__ {int offset; } ;
struct TYPE_6__ {int bits_per_pixel; int xres; TYPE_1__ red; int /*<<< orphan*/  pixclock; } ;
struct TYPE_5__ {int line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_3__ var; TYPE_2__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  asiliant_calc_dclk2 (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  asiliant_set_timing (struct fb_info*) ; 
 int /*<<< orphan*/  write_xr (int,int) ; 

__attribute__((used)) static int asiliantfb_set_par(struct fb_info *p)
{
	u8 dclk2_m;		/* Holds m-2 value for register */
	u8 dclk2_n;		/* Holds n-2 value for register */
	u8 dclk2_div;		/* Holds divisor bitmask */

	/* Set pixclock */
	asiliant_calc_dclk2(&p->var.pixclock, &dclk2_m, &dclk2_n, &dclk2_div);

	/* Set color depth */
	if (p->var.bits_per_pixel == 24) {
		write_xr(0x81, 0x16);	/* 24 bit packed color mode */
		write_xr(0x82, 0x00);	/* Disable palettes */
		write_xr(0x20, 0x20);	/* 24 bit blitter mode */
	} else if (p->var.bits_per_pixel == 16) {
		if (p->var.red.offset == 11)
			write_xr(0x81, 0x15);	/* 16 bit color mode */
		else
			write_xr(0x81, 0x14);	/* 15 bit color mode */
		write_xr(0x82, 0x00);	/* Disable palettes */
		write_xr(0x20, 0x10);	/* 16 bit blitter mode */
	} else if (p->var.bits_per_pixel == 8) {
		write_xr(0x0a, 0x02);	/* Linear */
		write_xr(0x81, 0x12);	/* 8 bit color mode */
		write_xr(0x82, 0x00);	/* Graphics gamma enable */
		write_xr(0x20, 0x00);	/* 8 bit blitter mode */
	}
	p->fix.line_length = p->var.xres * (p->var.bits_per_pixel >> 3);
	p->fix.visual = (p->var.bits_per_pixel == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	write_xr(0xc4, dclk2_m);
	write_xr(0xc5, dclk2_n);
	write_xr(0xc7, dclk2_div);
	/* Set up the CR registers */
	asiliant_set_timing(p);
	return 0;
}