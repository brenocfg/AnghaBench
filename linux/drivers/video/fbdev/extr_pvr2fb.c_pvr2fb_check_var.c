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
struct pvr2fb_par {unsigned int borderstop_h; unsigned int diwstart_h; unsigned int borderstart_h; unsigned int hsync_total; unsigned int diwstart_v; unsigned int borderstart_v; unsigned int borderstop_v; unsigned int vsync_total; } ;
struct fb_var_screeninfo {scalar_t__ pixclock; int xres; int yres; int xres_virtual; int yres_virtual; int bits_per_pixel; int vmode; scalar_t__ xoffset; scalar_t__ yoffset; int sync; int activate; unsigned int right_margin; unsigned int left_margin; unsigned int hsync_len; unsigned int upper_margin; unsigned int lower_margin; unsigned int vsync_len; } ;
struct TYPE_2__ {unsigned long smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FB_ACTIVATE_MASK ; 
 int FB_ACTIVATE_TEST ; 
 int FB_SYNC_BROADCAST ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_NONINTERLACED ; 
 int FB_VMODE_YWRAP ; 
 unsigned int NTSC_HTOTAL ; 
 int NTSC_VTOTAL ; 
 unsigned int PAL_HTOTAL ; 
 int PAL_VTOTAL ; 
 scalar_t__ TV_CLK ; 
 scalar_t__ VGA_CLK ; 
 scalar_t__ VO_VGA ; 
 unsigned long get_line_length (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  set_color_bitfields (struct fb_var_screeninfo*) ; 
 scalar_t__ video_output ; 

__attribute__((used)) static int pvr2fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct pvr2fb_par *par = (struct pvr2fb_par *)info->par;
	unsigned int vtotal, hsync_total;
	unsigned long line_length;

	if (var->pixclock != TV_CLK && var->pixclock != VGA_CLK) {
		pr_debug("Invalid pixclock value %d\n", var->pixclock);
		return -EINVAL;
	}

	if (var->xres < 320)
		var->xres = 320;
	if (var->yres < 240)
		var->yres = 240;
	if (var->xres_virtual < var->xres)
		var->xres_virtual = var->xres;
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;

	if (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	else if (var->bits_per_pixel <= 24)
		var->bits_per_pixel = 24;
	else if (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;

	set_color_bitfields(var);

	if (var->vmode & FB_VMODE_YWRAP) {
		if (var->xoffset || var->yoffset >= var->yres_virtual) {
			var->xoffset = var->yoffset = 0;
		} else {
			if (var->xoffset > var->xres_virtual - var->xres ||
			    var->yoffset > var->yres_virtual - var->yres)
				var->xoffset = var->yoffset = 0;
		}
	} else {
		var->xoffset = var->yoffset = 0;
	}

	/*
	 * XXX: Need to be more creative with this (i.e. allow doublecan for
	 * PAL/NTSC output).
	 */
	if (var->yres < 480 && video_output == VO_VGA)
		var->vmode |= FB_VMODE_DOUBLE;

	if (video_output != VO_VGA) {
		var->sync |= FB_SYNC_BROADCAST;
		var->vmode |= FB_VMODE_INTERLACED;
	} else {
		var->sync &= ~FB_SYNC_BROADCAST;
		var->vmode &= ~FB_VMODE_INTERLACED;
		var->vmode |= FB_VMODE_NONINTERLACED;
	}

	if ((var->activate & FB_ACTIVATE_MASK) != FB_ACTIVATE_TEST) {
		var->right_margin = par->borderstop_h -
				   (par->diwstart_h + var->xres);
		var->left_margin  = par->diwstart_h - par->borderstart_h;
		var->hsync_len    = par->borderstart_h +
		                   (par->hsync_total - par->borderstop_h);

		var->upper_margin = par->diwstart_v - par->borderstart_v;
		var->lower_margin = par->borderstop_v -
				   (par->diwstart_v + var->yres);
		var->vsync_len    = par->borderstop_v +
				   (par->vsync_total - par->borderstop_v);
	}

	hsync_total = var->left_margin + var->xres + var->right_margin +
		      var->hsync_len;
	vtotal = var->upper_margin + var->yres + var->lower_margin +
		 var->vsync_len;

	if (var->sync & FB_SYNC_BROADCAST) {
		if (var->vmode & FB_VMODE_INTERLACED)
			vtotal /= 2;
		if (vtotal > (PAL_VTOTAL + NTSC_VTOTAL)/2) {
			/* PAL video output */
			/* XXX: Should be using a range here ... ? */
			if (hsync_total != PAL_HTOTAL) {
				pr_debug("invalid hsync total for PAL\n");
				return -EINVAL;
			}
		} else {
			/* NTSC video output */
			if (hsync_total != NTSC_HTOTAL) {
				pr_debug("invalid hsync total for NTSC\n");
				return -EINVAL;
			}
		}
	}

	/* Check memory sizes */
	line_length = get_line_length(var->xres_virtual, var->bits_per_pixel);
	if (line_length * var->yres_virtual > info->fix.smem_len)
		return -ENOMEM;

	return 0;
}