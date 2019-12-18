#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lynxfb_output {int dummy; } ;
struct lynxfb_crtc {int /*<<< orphan*/  line_pad; } ;
struct lynxfb_par {struct lynxfb_output output; struct lynxfb_crtc crtc; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_6__ {int offset; int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {int xres_virtual; int bits_per_pixel; int height; int width; scalar_t__ accel_flags; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; TYPE_1__ transp; } ;
struct fb_fix_screeninfo {unsigned int line_length; void* visual; } ;
struct fb_info {struct fb_fix_screeninfo fix; struct fb_var_screeninfo var; struct lynxfb_par* par; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int hw_sm750_crtc_setMode (struct lynxfb_crtc*,struct fb_var_screeninfo*,struct fb_fix_screeninfo*) ; 
 int hw_sm750_output_setMode (struct lynxfb_output*,struct fb_var_screeninfo*,struct fb_fix_screeninfo*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static int lynxfb_ops_set_par(struct fb_info *info)
{
	struct lynxfb_par *par;
	struct lynxfb_crtc *crtc;
	struct lynxfb_output *output;
	struct fb_var_screeninfo *var;
	struct fb_fix_screeninfo *fix;
	int ret;
	unsigned int line_length;

	if (!info)
		return -EINVAL;

	ret = 0;
	par = info->par;
	crtc = &par->crtc;
	output = &par->output;
	var = &info->var;
	fix = &info->fix;

	/* fix structure is not so FIX ... */
	line_length = var->xres_virtual * var->bits_per_pixel / 8;
	line_length = ALIGN(line_length, crtc->line_pad);
	fix->line_length = line_length;
	pr_info("fix->line_length = %d\n", fix->line_length);

	/*
	 * var->red,green,blue,transp are need to be set by driver
	 * and these data should be set before setcolreg routine
	 */

	switch (var->bits_per_pixel) {
	case 8:
		fix->visual = FB_VISUAL_PSEUDOCOLOR;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.length = 0;
		var->transp.offset = 0;
		break;
	case 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.length = 0;
		var->transp.offset = 0;
		fix->visual = FB_VISUAL_TRUECOLOR;
		break;
	case 24:
	case 32:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		fix->visual = FB_VISUAL_TRUECOLOR;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	var->height = var->width = -1;
	var->accel_flags = 0;/*FB_ACCELF_TEXT;*/

	if (ret) {
		pr_err("pixel bpp format not satisfied\n.");
		return ret;
	}
	ret = hw_sm750_crtc_setMode(crtc, var, fix);
	if (!ret)
		ret = hw_sm750_output_setMode(output, var, fix);
	return ret;
}