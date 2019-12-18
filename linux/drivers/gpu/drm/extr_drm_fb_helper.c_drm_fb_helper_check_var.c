#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  msb_right; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int /*<<< orphan*/  msb_right; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {int /*<<< orphan*/  msb_right; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  msb_right; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct fb_var_screeninfo {scalar_t__ pixclock; int bits_per_pixel; scalar_t__ xres; scalar_t__ yres; scalar_t__ xres_virtual; scalar_t__ yres_virtual; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
struct fb_info {int /*<<< orphan*/  var; struct drm_fb_helper* par; } ;
struct drm_framebuffer {scalar_t__ width; scalar_t__ height; TYPE_5__* format; } ;
struct drm_fb_helper {struct drm_framebuffer* fb; } ;
struct TYPE_11__ {int* cpp; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_fb_helper_fill_pixel_fmt (struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_pixel_format_equal (struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 
 int drm_format_info_block_height (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int drm_format_info_block_width (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_dbg_master () ; 

int drm_fb_helper_check_var(struct fb_var_screeninfo *var,
			    struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_framebuffer *fb = fb_helper->fb;

	if (in_dbg_master())
		return -EINVAL;

	if (var->pixclock != 0) {
		DRM_DEBUG("fbdev emulation doesn't support changing the pixel clock, value of pixclock is ignored\n");
		var->pixclock = 0;
	}

	if ((drm_format_info_block_width(fb->format, 0) > 1) ||
	    (drm_format_info_block_height(fb->format, 0) > 1))
		return -EINVAL;

	/*
	 * Changes struct fb_var_screeninfo are currently not pushed back
	 * to KMS, hence fail if different settings are requested.
	 */
	if (var->bits_per_pixel != fb->format->cpp[0] * 8 ||
	    var->xres > fb->width || var->yres > fb->height ||
	    var->xres_virtual > fb->width || var->yres_virtual > fb->height) {
		DRM_DEBUG("fb requested width/height/bpp can't fit in current fb "
			  "request %dx%d-%d (virtual %dx%d) > %dx%d-%d\n",
			  var->xres, var->yres, var->bits_per_pixel,
			  var->xres_virtual, var->yres_virtual,
			  fb->width, fb->height, fb->format->cpp[0] * 8);
		return -EINVAL;
	}

	/*
	 * Workaround for SDL 1.2, which is known to be setting all pixel format
	 * fields values to zero in some cases. We treat this situation as a
	 * kind of "use some reasonable autodetected values".
	 */
	if (!var->red.offset     && !var->green.offset    &&
	    !var->blue.offset    && !var->transp.offset   &&
	    !var->red.length     && !var->green.length    &&
	    !var->blue.length    && !var->transp.length   &&
	    !var->red.msb_right  && !var->green.msb_right &&
	    !var->blue.msb_right && !var->transp.msb_right) {
		drm_fb_helper_fill_pixel_fmt(var, fb->format->depth);
	}

	/*
	 * drm fbdev emulation doesn't support changing the pixel format at all,
	 * so reject all pixel format changing requests.
	 */
	if (!drm_fb_pixel_format_equal(var, &info->var)) {
		DRM_DEBUG("fbdev emulation doesn't support changing the pixel format\n");
		return -EINVAL;
	}

	return 0;
}