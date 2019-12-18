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
struct TYPE_6__ {unsigned int len_usable; } ;
struct matroxfb_dh_fb_info {TYPE_1__ video; } ;
struct TYPE_10__ {int offset; int length; } ;
struct TYPE_9__ {int length; scalar_t__ offset; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int yres_virtual; int yres; int xres_virtual; int xres; int xoffset; int yoffset; int left_margin; int right_margin; int hsync_len; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_VISUAL_TRUECOLOR ; 

__attribute__((used)) static int matroxfb_dh_decode_var(struct matroxfb_dh_fb_info* m2info,
		struct fb_var_screeninfo* var,
		int *visual,
		int *video_cmap_len,
		int *mode) {
	unsigned int mask;
	unsigned int memlen;
	unsigned int vramlen;

	switch (var->bits_per_pixel) {
		case 16:	mask = 0x1F;
				break;
		case 32:	mask = 0x0F;
				break;
		default:	return -EINVAL;
	}
	vramlen = m2info->video.len_usable;
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;
	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	var->xres_virtual = (var->xres_virtual + mask) & ~mask;
	if (var->yres_virtual > 32767)
		return -EINVAL;
	memlen = var->xres_virtual * var->yres_virtual * (var->bits_per_pixel >> 3);
	if (memlen > vramlen)
		return -EINVAL;
	if (var->xoffset + var->xres > var->xres_virtual)
		var->xoffset = var->xres_virtual - var->xres;
	if (var->yoffset + var->yres > var->yres_virtual)
		var->yoffset = var->yres_virtual - var->yres;

	var->xres &= ~7;
	var->left_margin &= ~7;
	var->right_margin &= ~7;
	var->hsync_len &= ~7;

	*mode = var->bits_per_pixel;
	if (var->bits_per_pixel == 16) {
		if (var->green.length == 5) {
			var->red.offset = 10;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 5;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 15;
			var->transp.length = 1;
			*mode = 15;
		} else {
			var->red.offset = 11;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		}
	} else {
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
	}
	*visual = FB_VISUAL_TRUECOLOR;
	*video_cmap_len = 16;
	return 0;
}