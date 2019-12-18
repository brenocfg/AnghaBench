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
struct pxa168fb_info {scalar_t__ reg_base; } ;
struct fb_var_screeninfo {int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; } ;
struct fb_info {struct fb_var_screeninfo var; struct pxa168fb_info* par; } ;

/* Variables and functions */
 scalar_t__ LCD_SPUT_V_H_TOTAL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_dumb_screen_dimensions(struct fb_info *info)
{
	struct pxa168fb_info *fbi = info->par;
	struct fb_var_screeninfo *v = &info->var;
	int x;
	int y;

	x = v->xres + v->right_margin + v->hsync_len + v->left_margin;
	y = v->yres + v->lower_margin + v->vsync_len + v->upper_margin;

	writel((y << 16) | x, fbi->reg_base + LCD_SPUT_V_H_TOTAL);
}