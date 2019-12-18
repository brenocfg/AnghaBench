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
struct fb_var_screeninfo {int vmode; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fb_info {struct amifb_par* par; } ;
struct amifb_par {int vmode; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;

/* Variables and functions */
 int FB_VMODE_YWRAP ; 
 int /*<<< orphan*/  ami_update_par (struct fb_info*) ; 
 int do_vmode_pan ; 

__attribute__((used)) static void ami_pan_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct amifb_par *par = info->par;

	par->xoffset = var->xoffset;
	par->yoffset = var->yoffset;
	if (var->vmode & FB_VMODE_YWRAP)
		par->vmode |= FB_VMODE_YWRAP;
	else
		par->vmode &= ~FB_VMODE_YWRAP;

	do_vmode_pan = 0;
	ami_update_par(info);
	do_vmode_pan = 1;
}