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
struct vmw_private {int dummy; } ;
struct vmw_fb_par {scalar_t__ max_width; scalar_t__ max_height; struct vmw_private* vmw_priv; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int offset; int length; } ;
struct TYPE_5__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; scalar_t__ xoffset; int xres; scalar_t__ yoffset; scalar_t__ yres; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {struct vmw_fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  vmw_kms_validate_mode_vram (struct vmw_private*,int,scalar_t__) ; 

__attribute__((used)) static int vmw_fb_check_var(struct fb_var_screeninfo *var,
			    struct fb_info *info)
{
	int depth = var->bits_per_pixel;
	struct vmw_fb_par *par = info->par;
	struct vmw_private *vmw_priv = par->vmw_priv;

	switch (var->bits_per_pixel) {
	case 32:
		depth = (var->transp.length > 0) ? 32 : 24;
		break;
	default:
		DRM_ERROR("Bad bpp %u.\n", var->bits_per_pixel);
		return -EINVAL;
	}

	switch (depth) {
	case 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 0;
		var->transp.offset = 0;
		break;
	case 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 8;
		var->transp.offset = 24;
		break;
	default:
		DRM_ERROR("Bad depth %u.\n", depth);
		return -EINVAL;
	}

	if ((var->xoffset + var->xres) > par->max_width ||
	    (var->yoffset + var->yres) > par->max_height) {
		DRM_ERROR("Requested geom can not fit in framebuffer\n");
		return -EINVAL;
	}

	if (!vmw_kms_validate_mode_vram(vmw_priv,
					var->xres * var->bits_per_pixel/8,
					var->yoffset + var->yres)) {
		DRM_ERROR("Requested geom can not fit in framebuffer\n");
		return -EINVAL;
	}

	return 0;
}