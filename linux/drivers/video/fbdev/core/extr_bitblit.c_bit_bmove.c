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
struct vc_data {TYPE_1__ vc_font; } ;
struct fb_info {TYPE_2__* fbops; } ;
struct fb_copyarea {int sx; int sy; int dx; int dy; int height; int width; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_copyarea ) (struct fb_info*,struct fb_copyarea*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_copyarea*) ; 

__attribute__((used)) static void bit_bmove(struct vc_data *vc, struct fb_info *info, int sy,
		      int sx, int dy, int dx, int height, int width)
{
	struct fb_copyarea area;

	area.sx = sx * vc->vc_font.width;
	area.sy = sy * vc->vc_font.height;
	area.dx = dx * vc->vc_font.width;
	area.dy = dy * vc->vc_font.height;
	area.height = height * vc->vc_font.height;
	area.width = width * vc->vc_font.width;

	info->fbops->fb_copyarea(info, &area);
}