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
struct geodefb_par {scalar_t__ dc_regs; } ;
struct fb_info {struct geodefb_par* par; } ;

/* Variables and functions */
 scalar_t__ DC_PAL_ADDRESS ; 
 scalar_t__ DC_PAL_DATA ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gx1_set_hw_palette_reg(struct fb_info *info, unsigned regno,
				   unsigned red, unsigned green, unsigned blue)
{
	struct geodefb_par *par = info->par;
	int val;

	/* Hardware palette is in RGB 6-6-6 format. */
	val  = (red   <<  2) & 0x3f000;
	val |= (green >>  4) & 0x00fc0;
	val |= (blue  >> 10) & 0x0003f;

	writel(regno, par->dc_regs + DC_PAL_ADDRESS);
	writel(val, par->dc_regs + DC_PAL_DATA);
}