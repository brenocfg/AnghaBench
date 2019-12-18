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
struct lynxfb_crtc {int vidmem_size; int /*<<< orphan*/  line_pad; } ;
struct lynxfb_par {struct lynxfb_crtc crtc; } ;
struct TYPE_9__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int height; int width; int xres_virtual; int yres_virtual; scalar_t__ accel_flags; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; TYPE_1__ transp; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_10__ {void* visual; } ;
struct fb_info {TYPE_5__ fix; struct lynxfb_par* par; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int hw_sm750_crtc_checkMode (struct lynxfb_crtc*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int lynxfb_ops_check_var(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct lynxfb_par *par;
	struct lynxfb_crtc *crtc;
	resource_size_t request;

	par = info->par;
	crtc = &par->crtc;

	pr_debug("check var:%dx%d-%d\n",
		 var->xres,
		 var->yres,
		 var->bits_per_pixel);

	switch (var->bits_per_pixel) {
	case 8:
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
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
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		break;
	case 24:
	case 32:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		break;
	default:
		pr_err("bpp %d not supported\n", var->bits_per_pixel);
		return -EINVAL;
	}
	var->height = var->width = -1;
	var->accel_flags = 0;/* FB_ACCELF_TEXT; */

	/* check if current fb's video memory big enought to hold the onscreen*/
	request = var->xres_virtual * (var->bits_per_pixel >> 3);
	/* defaulty crtc->channel go with par->index */

	request = ALIGN(request, crtc->line_pad);
	request = request * var->yres_virtual;
	if (crtc->vidmem_size < request) {
		pr_err("not enough video memory for mode\n");
		return -ENOMEM;
	}

	return hw_sm750_crtc_checkMode(crtc, var);
}