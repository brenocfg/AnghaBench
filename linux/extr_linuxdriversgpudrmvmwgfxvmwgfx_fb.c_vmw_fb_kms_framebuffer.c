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
struct drm_framebuffer {int width; scalar_t__ height; int* pitches; TYPE_1__* format; } ;
struct vmw_framebuffer {struct drm_framebuffer base; } ;
struct vmw_fb_par {size_t bo_size; struct drm_framebuffer* set_fb; int /*<<< orphan*/  vmw_bo; int /*<<< orphan*/  vmw_priv; } ;
struct fb_var_screeninfo {int xres; scalar_t__ yres; int bits_per_pixel; } ;
struct fb_info {struct fb_var_screeninfo var; struct vmw_fb_par* par; } ;
struct drm_mode_fb_cmd2 {int width; scalar_t__ height; int* pitches; scalar_t__ pixel_format; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ IS_ERR (struct vmw_framebuffer*) ; 
 int PTR_ERR (struct vmw_framebuffer*) ; 
 scalar_t__ drm_mode_legacy_fb_format (int,int) ; 
 int vmw_fb_compute_depth (struct fb_var_screeninfo*,int*) ; 
 int vmw_fb_create_bo (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int vmw_fb_kms_detach (struct vmw_fb_par*,int,int) ; 
 struct vmw_framebuffer* vmw_kms_new_framebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct drm_mode_fb_cmd2*) ; 

__attribute__((used)) static int vmw_fb_kms_framebuffer(struct fb_info *info)
{
	struct drm_mode_fb_cmd2 mode_cmd;
	struct vmw_fb_par *par = info->par;
	struct fb_var_screeninfo *var = &info->var;
	struct drm_framebuffer *cur_fb;
	struct vmw_framebuffer *vfb;
	int ret = 0, depth;
	size_t new_bo_size;

	ret = vmw_fb_compute_depth(var, &depth);
	if (ret)
		return ret;

	mode_cmd.width = var->xres;
	mode_cmd.height = var->yres;
	mode_cmd.pitches[0] = ((var->bits_per_pixel + 7) / 8) * mode_cmd.width;
	mode_cmd.pixel_format =
		drm_mode_legacy_fb_format(var->bits_per_pixel, depth);

	cur_fb = par->set_fb;
	if (cur_fb && cur_fb->width == mode_cmd.width &&
	    cur_fb->height == mode_cmd.height &&
	    cur_fb->format->format == mode_cmd.pixel_format &&
	    cur_fb->pitches[0] == mode_cmd.pitches[0])
		return 0;

	/* Need new buffer object ? */
	new_bo_size = (size_t) mode_cmd.pitches[0] * (size_t) mode_cmd.height;
	ret = vmw_fb_kms_detach(par,
				par->bo_size < new_bo_size ||
				par->bo_size > 2*new_bo_size,
				true);
	if (ret)
		return ret;

	if (!par->vmw_bo) {
		ret = vmw_fb_create_bo(par->vmw_priv, new_bo_size,
				       &par->vmw_bo);
		if (ret) {
			DRM_ERROR("Failed creating a buffer object for "
				  "fbdev.\n");
			return ret;
		}
		par->bo_size = new_bo_size;
	}

	vfb = vmw_kms_new_framebuffer(par->vmw_priv, par->vmw_bo, NULL,
				      true, &mode_cmd);
	if (IS_ERR(vfb))
		return PTR_ERR(vfb);

	par->set_fb = &vfb->base;

	return 0;
}