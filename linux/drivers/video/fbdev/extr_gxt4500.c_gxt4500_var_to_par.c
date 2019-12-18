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
struct gxt4500_par {void* pixfmt; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {int xres; int xoffset; int xres_virtual; scalar_t__ yres; scalar_t__ yoffset; scalar_t__ yres_virtual; int vmode; int bits_per_pixel; TYPE_2__ green; TYPE_1__ transp; int /*<<< orphan*/  pixclock; } ;

/* Variables and functions */
 void* DFA_PIX_16BIT_1555 ; 
 void* DFA_PIX_16BIT_565 ; 
 void* DFA_PIX_24BIT ; 
 void* DFA_PIX_32BIT ; 
 void* DFA_PIX_8BIT ; 
 int EINVAL ; 
 int FB_VMODE_MASK ; 
 int FB_VMODE_NONINTERLACED ; 
 scalar_t__ calc_pll (int /*<<< orphan*/ ,struct gxt4500_par*) ; 

__attribute__((used)) static int gxt4500_var_to_par(struct fb_var_screeninfo *var,
			      struct gxt4500_par *par)
{
	if (var->xres + var->xoffset > var->xres_virtual ||
	    var->yres + var->yoffset > var->yres_virtual ||
	    var->xres_virtual > 4096)
		return -EINVAL;
	if ((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		return -EINVAL;

	if (calc_pll(var->pixclock, par) < 0)
		return -EINVAL;

	switch (var->bits_per_pixel) {
	case 32:
		if (var->transp.length)
			par->pixfmt = DFA_PIX_32BIT;
		else
			par->pixfmt = DFA_PIX_24BIT;
		break;
	case 24:
		par->pixfmt = DFA_PIX_24BIT;
		break;
	case 16:
		if (var->green.length == 5)
			par->pixfmt = DFA_PIX_16BIT_1555;
		else
			par->pixfmt = DFA_PIX_16BIT_565;
		break;
	case 8:
		par->pixfmt = DFA_PIX_8BIT;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}