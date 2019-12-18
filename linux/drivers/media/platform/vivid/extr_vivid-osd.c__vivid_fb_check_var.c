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
struct vivid_dev {int dummy; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_6__ {int length; int offset; } ;
struct TYPE_5__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int hsync_len; int vsync_len; int pixclock; int right_margin; int lower_margin; int /*<<< orphan*/  vmode; scalar_t__ nonstd; scalar_t__ upper_margin; scalar_t__ left_margin; scalar_t__ yoffset; scalar_t__ xoffset; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VMODE_MASK ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*) ; 

__attribute__((used)) static int _vivid_fb_check_var(struct fb_var_screeninfo *var, struct vivid_dev *dev)
{
	dprintk(dev, 1, "vivid_fb_check_var\n");

	var->bits_per_pixel = 16;
	if (var->green.length == 5) {
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
	} else {
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
	}
	var->xoffset = var->yoffset = 0;
	var->left_margin = var->upper_margin = 0;
	var->nonstd = 0;

	var->vmode &= ~FB_VMODE_MASK;
	var->vmode |= FB_VMODE_NONINTERLACED;

	/* Dummy values */
	var->hsync_len = 24;
	var->vsync_len = 2;
	var->pixclock = 84316;
	var->right_margin = 776;
	var->lower_margin = 591;
	return 0;
}