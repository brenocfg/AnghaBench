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
typedef  int u_int ;
typedef  int u32 ;
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {int bits_per_pixel; TYPE_1__ green; } ;
struct fb_info {int* pseudo_palette; TYPE_2__ var; scalar_t__ par; } ;
struct atyfb_par {TYPE_3__* palette; scalar_t__ asleep; } ;
struct TYPE_6__ {int red; int green; int blue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_CNTL ; 
 int /*<<< orphan*/  DAC_MASK ; 
 int /*<<< orphan*/  EXTRA_BRIGHT ; 
 int /*<<< orphan*/  INTEGRATED ; 
 scalar_t__ M64_HAS (int /*<<< orphan*/ ) ; 
 int aty_ld_8 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_pal (int,int,int,int,struct atyfb_par*) ; 

__attribute__((used)) static int atyfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int transp, struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	int i, depth;
	u32 *pal = info->pseudo_palette;

	depth = info->var.bits_per_pixel;
	if (depth == 16)
		depth = (info->var.green.length == 5) ? 15 : 16;

	if (par->asleep)
		return 0;

	if (regno > 255 ||
	    (depth == 16 && regno > 63) ||
	    (depth == 15 && regno > 31))
		return 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	par->palette[regno].red = red;
	par->palette[regno].green = green;
	par->palette[regno].blue = blue;

	if (regno < 16) {
		switch (depth) {
		case 15:
			pal[regno] = (regno << 10) | (regno << 5) | regno;
			break;
		case 16:
			pal[regno] = (regno << 11) | (regno << 5) | regno;
			break;
		case 24:
			pal[regno] = (regno << 16) | (regno << 8) | regno;
			break;
		case 32:
			i = (regno << 8) | regno;
			pal[regno] = (i << 16) | i;
			break;
		}
	}

	i = aty_ld_8(DAC_CNTL, par) & 0xfc;
	if (M64_HAS(EXTRA_BRIGHT))
		i |= 0x2; /* DAC_CNTL | 0x2 turns off the extra brightness for gt */
	aty_st_8(DAC_CNTL, i, par);
	aty_st_8(DAC_MASK, 0xff, par);

	if (M64_HAS(INTEGRATED)) {
		if (depth == 16) {
			if (regno < 32)
				aty_st_pal(regno << 3, red,
					   par->palette[regno << 1].green,
					   blue, par);
			red = par->palette[regno >> 1].red;
			blue = par->palette[regno >> 1].blue;
			regno <<= 2;
		} else if (depth == 15) {
			regno <<= 3;
			for (i = 0; i < 8; i++)
				aty_st_pal(regno + i, red, green, blue, par);
		}
	}
	aty_st_pal(regno, red, green, blue, par);

	return 0;
}