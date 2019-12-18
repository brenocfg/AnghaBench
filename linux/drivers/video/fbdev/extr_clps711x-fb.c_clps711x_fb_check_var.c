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
typedef  int u32 ;
struct TYPE_4__ {int length; scalar_t__ offset; scalar_t__ msb_right; } ;
struct TYPE_3__ {scalar_t__ length; scalar_t__ offset; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int yres; int grayscale; TYPE_2__ red; TYPE_2__ blue; TYPE_2__ green; TYPE_1__ transp; int /*<<< orphan*/  pixclock; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int CLPS711X_FB_BPP_MAX ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 

__attribute__((used)) static int clps711x_fb_check_var(struct fb_var_screeninfo *var,
				 struct fb_info *info)
{
	u32 val;

	if (var->bits_per_pixel < 1 ||
	    var->bits_per_pixel > CLPS711X_FB_BPP_MAX)
		return -EINVAL;

	if (!var->pixclock)
		return -EINVAL;

	val = DIV_ROUND_UP(var->xres, 16) - 1;
	if (val < 0x01 || val > 0x3f)
		return -EINVAL;

	val = DIV_ROUND_UP(var->yres * var->xres * var->bits_per_pixel, 128);
	val--;
	if (val < 0x001 || val > 0x1fff)
		return -EINVAL;

	var->transp.msb_right	= 0;
	var->transp.offset	= 0;
	var->transp.length	= 0;
	var->red.msb_right	= 0;
	var->red.offset		= 0;
	var->red.length		= var->bits_per_pixel;
	var->green		= var->red;
	var->blue		= var->red;
	var->grayscale		= var->bits_per_pixel > 1;

	return 0;
}