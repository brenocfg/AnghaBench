#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_var_screeninfo {int bits_per_pixel; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  var_to_depth (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int pxafb_var_to_bpp(struct fb_var_screeninfo *var)
{
	int bpp = -EINVAL;

	switch (var->bits_per_pixel) {
	case 1:  bpp = 0; break;
	case 2:  bpp = 1; break;
	case 4:  bpp = 2; break;
	case 8:  bpp = 3; break;
	case 16: bpp = 4; break;
	case 24:
		switch (var_to_depth(var)) {
		case 18: bpp = 6; break; /* 18-bits/pixel packed */
		case 19: bpp = 8; break; /* 19-bits/pixel packed */
		case 24: bpp = 9; break;
		}
		break;
	case 32:
		switch (var_to_depth(var)) {
		case 18: bpp = 5; break; /* 18-bits/pixel unpacked */
		case 19: bpp = 7; break; /* 19-bits/pixel unpacked */
		case 25: bpp = 10; break;
		}
		break;
	}
	return bpp;
}