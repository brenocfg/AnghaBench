#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; int left_margin; int right_margin; int upper_margin; int lower_margin; int hsync_len; int vsync_len; int pixclock; int height; int width; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; TYPE_1__ transp; } ;
struct intelfb_info {int initial_vga; int initial_video_ram; int /*<<< orphan*/  initial_pitch; int /*<<< orphan*/  initial_fb_base; struct fb_var_screeninfo initial_var; } ;
struct TYPE_10__ {int lfb_size; int lfb_width; int lfb_height; int lfb_depth; int red_size; int green_size; int blue_size; int /*<<< orphan*/  rsvd_size; int /*<<< orphan*/  rsvd_pos; int /*<<< orphan*/  blue_pos; int /*<<< orphan*/  green_pos; int /*<<< orphan*/  red_pos; int /*<<< orphan*/  lfb_linelength; int /*<<< orphan*/  lfb_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BtoKB (int) ; 
 int /*<<< orphan*/  DBG_MSG (char*,...) ; 
 int KB (int) ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ screen_info ; 

__attribute__((used)) static void get_initial_mode(struct intelfb_info *dinfo)
{
	struct fb_var_screeninfo *var;
	int xtot, ytot;

	DBG_MSG("get_initial_mode\n");

	dinfo->initial_vga = 1;
	dinfo->initial_fb_base = screen_info.lfb_base;
	dinfo->initial_video_ram = screen_info.lfb_size * KB(64);
	dinfo->initial_pitch = screen_info.lfb_linelength;

	var = &dinfo->initial_var;
	memset(var, 0, sizeof(*var));
	var->xres = screen_info.lfb_width;
	var->yres = screen_info.lfb_height;
	var->bits_per_pixel = screen_info.lfb_depth;
	switch (screen_info.lfb_depth) {
	case 15:
		var->bits_per_pixel = 16;
		break;
	case 24:
		var->bits_per_pixel = 32;
		break;
	}

	DBG_MSG("Initial info: FB is 0x%x/0x%x (%d kByte)\n",
		dinfo->initial_fb_base, dinfo->initial_video_ram,
		BtoKB(dinfo->initial_video_ram));

	DBG_MSG("Initial info: mode is %dx%d-%d (%d)\n",
		var->xres, var->yres, var->bits_per_pixel,
		dinfo->initial_pitch);

	/* Dummy timing values (assume 60Hz) */
	var->left_margin = (var->xres / 8) & 0xf8;
	var->right_margin = 32;
	var->upper_margin = 16;
	var->lower_margin = 4;
	var->hsync_len = (var->xres / 8) & 0xf8;
	var->vsync_len = 4;

	xtot = var->xres + var->left_margin +
		var->right_margin + var->hsync_len;
	ytot = var->yres + var->upper_margin +
		var->lower_margin + var->vsync_len;
	var->pixclock = 10000000 / xtot * 1000 / ytot * 100 / 60;

	var->height = -1;
	var->width = -1;

	if (var->bits_per_pixel > 8) {
		var->red.offset = screen_info.red_pos;
		var->red.length = screen_info.red_size;
		var->green.offset = screen_info.green_pos;
		var->green.length = screen_info.green_size;
		var->blue.offset = screen_info.blue_pos;
		var->blue.length = screen_info.blue_size;
		var->transp.offset = screen_info.rsvd_pos;
		var->transp.length = screen_info.rsvd_size;
	} else {
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
	}
}