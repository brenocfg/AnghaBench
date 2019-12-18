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
struct TYPE_4__ {int line_length; int xpanstep; int /*<<< orphan*/  visual; } ;
struct TYPE_3__ {int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 

__attribute__((used)) static void savagefb_set_fix(struct fb_info *info)
{
	info->fix.line_length = info->var.xres_virtual *
		info->var.bits_per_pixel / 8;

	if (info->var.bits_per_pixel == 8) {
		info->fix.visual      = FB_VISUAL_PSEUDOCOLOR;
		info->fix.xpanstep    = 4;
	} else {
		info->fix.visual      = FB_VISUAL_TRUECOLOR;
		info->fix.xpanstep    = 2;
	}

}