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
struct TYPE_4__ {int line_length; int smem_start; } ;
struct TYPE_3__ {int xres_virtual; int bits_per_pixel; int yres; int xres; int /*<<< orphan*/  pixclock; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XXFB_LINE_LENGTH ; 
 int /*<<< orphan*/  EP93XXFB_SCREEN_LINES ; 
 int /*<<< orphan*/  EP93XXFB_SCREEN_PAGE ; 
 int /*<<< orphan*/  EP93XXFB_VLINE_STEP ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ep93xxfb_set_timing (struct fb_info*) ; 
 int /*<<< orphan*/  ep93xxfb_set_video_attribs (struct fb_info*) ; 
 int /*<<< orphan*/  ep93xxfb_writel (struct ep93xx_fbi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xxfb_set_par(struct fb_info *info)
{
	struct ep93xx_fbi *fbi = info->par;

	clk_set_rate(fbi->clk, 1000 * PICOS2KHZ(info->var.pixclock));

	ep93xxfb_set_timing(info);

	info->fix.line_length = info->var.xres_virtual *
		info->var.bits_per_pixel / 8;

	ep93xxfb_writel(fbi, info->fix.smem_start, EP93XXFB_SCREEN_PAGE);
	ep93xxfb_writel(fbi, info->var.yres - 1, EP93XXFB_SCREEN_LINES);
	ep93xxfb_writel(fbi, ((info->var.xres * info->var.bits_per_pixel)
			      / 32) - 1, EP93XXFB_LINE_LENGTH);
	ep93xxfb_writel(fbi, info->fix.line_length / 4, EP93XXFB_VLINE_STEP);
	ep93xxfb_set_video_attribs(info);
	return 0;
}