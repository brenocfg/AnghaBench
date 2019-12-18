#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sm501fb_par {struct sm501fb_info* info; } ;
struct sm501fb_info {scalar_t__ regs; } ;
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_2__ {int xres_virtual; int yres_virtual; } ;
struct fb_info {TYPE_1__ var; struct sm501fb_par* par; } ;

/* Variables and functions */
 scalar_t__ SM501_DC_PANEL_FB_HEIGHT ; 
 scalar_t__ SM501_DC_PANEL_FB_WIDTH ; 
 int /*<<< orphan*/  sm501fb_sync_regs (struct sm501fb_info*) ; 
 int /*<<< orphan*/  smc501_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int sm501fb_pan_pnl(struct fb_var_screeninfo *var,
			   struct fb_info *info)
{
	struct sm501fb_par  *par = info->par;
	struct sm501fb_info *fbi = par->info;
	unsigned long reg;

	reg = var->xoffset | (info->var.xres_virtual << 16);
	smc501_writel(reg, fbi->regs + SM501_DC_PANEL_FB_WIDTH);

	reg = var->yoffset | (info->var.yres_virtual << 16);
	smc501_writel(reg, fbi->regs + SM501_DC_PANEL_FB_HEIGHT);

	sm501fb_sync_regs(fbi);
	return 0;
}