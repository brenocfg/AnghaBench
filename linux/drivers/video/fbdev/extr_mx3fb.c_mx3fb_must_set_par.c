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
struct fb_var_screeninfo {int activate; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct mx3fb_info {struct fb_var_screeninfo cur_var; } ;
struct fb_info {struct fb_var_screeninfo var; struct mx3fb_info* par; } ;

/* Variables and functions */
 int FB_ACTIVATE_FORCE ; 
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  memcmp (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 

__attribute__((used)) static bool mx3fb_must_set_par(struct fb_info *fbi)
{
	struct mx3fb_info *mx3_fbi = fbi->par;
	struct fb_var_screeninfo old_var = mx3_fbi->cur_var;
	struct fb_var_screeninfo new_var = fbi->var;

	if ((fbi->var.activate & FB_ACTIVATE_FORCE) &&
	    (fbi->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		return true;

	/*
	 * Ignore xoffset and yoffset update,
	 * because pan display handles this case.
	 */
	old_var.xoffset = new_var.xoffset;
	old_var.yoffset = new_var.yoffset;

	return !!memcmp(&old_var, &new_var, sizeof(struct fb_var_screeninfo));
}