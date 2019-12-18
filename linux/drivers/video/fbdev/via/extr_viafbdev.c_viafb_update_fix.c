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
struct TYPE_4__ {int bits_per_pixel; int xres_virtual; } ;
struct TYPE_3__ {int /*<<< orphan*/  line_length; int /*<<< orphan*/  visual; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  VIA_PITCH_SIZE ; 

__attribute__((used)) static void viafb_update_fix(struct fb_info *info)
{
	u32 bpp = info->var.bits_per_pixel;

	info->fix.visual =
		bpp == 8 ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = ALIGN(info->var.xres_virtual * bpp / 8,
		VIA_PITCH_SIZE);
}