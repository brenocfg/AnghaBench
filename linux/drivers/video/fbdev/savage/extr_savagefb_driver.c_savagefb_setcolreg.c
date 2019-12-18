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
typedef  unsigned int u32 ;
struct savagefb_par {TYPE_1__* palette; } ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ var; struct savagefb_par* par; } ;
struct TYPE_3__ {unsigned int red; unsigned int green; unsigned int blue; unsigned int transp; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NR_PALETTE ; 
 int /*<<< orphan*/  vga_out8 (int,unsigned int,struct savagefb_par*) ; 

__attribute__((used)) static int savagefb_setcolreg(unsigned        regno,
			      unsigned        red,
			      unsigned        green,
			      unsigned        blue,
			      unsigned        transp,
			      struct fb_info *info)
{
	struct savagefb_par *par = info->par;

	if (regno >= NR_PALETTE)
		return -EINVAL;

	par->palette[regno].red    = red;
	par->palette[regno].green  = green;
	par->palette[regno].blue   = blue;
	par->palette[regno].transp = transp;

	switch (info->var.bits_per_pixel) {
	case 8:
		vga_out8(0x3c8, regno, par);

		vga_out8(0x3c9, red   >> 10, par);
		vga_out8(0x3c9, green >> 10, par);
		vga_out8(0x3c9, blue  >> 10, par);
		break;

	case 16:
		if (regno < 16)
			((u32 *)info->pseudo_palette)[regno] =
				((red   & 0xf800)      ) |
				((green & 0xfc00) >>  5) |
				((blue  & 0xf800) >> 11);
		break;

	case 24:
		if (regno < 16)
			((u32 *)info->pseudo_palette)[regno] =
				((red    & 0xff00) <<  8) |
				((green  & 0xff00)      ) |
				((blue   & 0xff00) >>  8);
		break;
	case 32:
		if (regno < 16)
			((u32 *)info->pseudo_palette)[regno] =
				((transp & 0xff00) << 16) |
				((red    & 0xff00) <<  8) |
				((green  & 0xff00)      ) |
				((blue   & 0xff00) >>  8);
		break;

	default:
		return 1;
	}

	return 0;
}