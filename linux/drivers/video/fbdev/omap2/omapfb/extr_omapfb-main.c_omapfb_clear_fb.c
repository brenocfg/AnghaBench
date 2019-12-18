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
struct TYPE_2__ {int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;
struct fb_info {TYPE_1__ var; } ;
struct fb_fillrect {int /*<<< orphan*/  rop; int /*<<< orphan*/  color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void omapfb_clear_fb(struct fb_info *fbi)
{
	const struct fb_fillrect rect = {
		.dx = 0,
		.dy = 0,
		.width = fbi->var.xres_virtual,
		.height = fbi->var.yres_virtual,
		.color = 0,
		.rop = ROP_COPY,
	};

	cfb_fillrect(fbi, &rect);
}