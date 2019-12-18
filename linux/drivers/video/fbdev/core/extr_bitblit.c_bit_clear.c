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
struct TYPE_3__ {int width; int height; } ;
struct vc_data {TYPE_1__ vc_font; scalar_t__ vc_hi_font_mask; } ;
struct fb_info {TYPE_2__* fbops; } ;
struct fb_fillrect {int dx; int dy; int width; int height; int /*<<< orphan*/  rop; int /*<<< orphan*/  color; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_fillrect ) (struct fb_info*,struct fb_fillrect*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  attr_bgcol_ec (int,struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_fillrect*) ; 

__attribute__((used)) static void bit_clear(struct vc_data *vc, struct fb_info *info, int sy,
		      int sx, int height, int width)
{
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	struct fb_fillrect region;

	region.color = attr_bgcol_ec(bgshift, vc, info);
	region.dx = sx * vc->vc_font.width;
	region.dy = sy * vc->vc_font.height;
	region.width = width * vc->vc_font.width;
	region.height = height * vc->vc_font.height;
	region.rop = ROP_COPY;

	info->fbops->fb_fillrect(info, &region);
}