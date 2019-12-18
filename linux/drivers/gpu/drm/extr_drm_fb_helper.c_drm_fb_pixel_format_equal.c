#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ offset; scalar_t__ length; scalar_t__ msb_right; } ;
struct TYPE_7__ {scalar_t__ offset; scalar_t__ length; scalar_t__ msb_right; } ;
struct TYPE_6__ {scalar_t__ offset; scalar_t__ length; scalar_t__ msb_right; } ;
struct TYPE_5__ {scalar_t__ offset; scalar_t__ length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {scalar_t__ bits_per_pixel; scalar_t__ grayscale; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */

__attribute__((used)) static bool drm_fb_pixel_format_equal(const struct fb_var_screeninfo *var_1,
				      const struct fb_var_screeninfo *var_2)
{
	return var_1->bits_per_pixel == var_2->bits_per_pixel &&
	       var_1->grayscale == var_2->grayscale &&
	       var_1->red.offset == var_2->red.offset &&
	       var_1->red.length == var_2->red.length &&
	       var_1->red.msb_right == var_2->red.msb_right &&
	       var_1->green.offset == var_2->green.offset &&
	       var_1->green.length == var_2->green.length &&
	       var_1->green.msb_right == var_2->green.msb_right &&
	       var_1->blue.offset == var_2->blue.offset &&
	       var_1->blue.length == var_2->blue.length &&
	       var_1->blue.msb_right == var_2->blue.msb_right &&
	       var_1->transp.offset == var_2->transp.offset &&
	       var_1->transp.length == var_2->transp.length &&
	       var_1->transp.msb_right == var_2->transp.msb_right;
}