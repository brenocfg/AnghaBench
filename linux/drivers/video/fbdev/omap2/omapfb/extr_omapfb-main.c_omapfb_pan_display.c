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
struct omapfb_info {int /*<<< orphan*/  region; int /*<<< orphan*/  id; } ;
struct fb_var_screeninfo {scalar_t__ xoffset; scalar_t__ yoffset; } ;
struct fb_info {struct fb_var_screeninfo var; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int omapfb_apply_changes (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapfb_pan_display(struct fb_var_screeninfo *var,
		struct fb_info *fbi)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct fb_var_screeninfo new_var;
	int r;

	DBG("pan_display(%d)\n", FB2OFB(fbi)->id);

	if (var->xoffset == fbi->var.xoffset &&
	    var->yoffset == fbi->var.yoffset)
		return 0;

	new_var = fbi->var;
	new_var.xoffset = var->xoffset;
	new_var.yoffset = var->yoffset;

	fbi->var = new_var;

	omapfb_get_mem_region(ofbi->region);

	r = omapfb_apply_changes(fbi, 0);

	omapfb_put_mem_region(ofbi->region);

	return r;
}