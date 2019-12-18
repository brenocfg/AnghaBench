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
struct fb_var_screeninfo {int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_graphics_start (struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa168fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	set_graphics_start(info, var->xoffset, var->yoffset);

	return 0;
}