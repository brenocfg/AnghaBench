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
struct drm_mode_fb_cmd2 {int flags; scalar_t__ width; scalar_t__ height; } ;
struct drm_mode_config {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; TYPE_1__* funcs; int /*<<< orphan*/  allow_fb_modifiers; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct TYPE_2__ {struct drm_framebuffer* (* fb_create ) (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_FB_INTERLACED ; 
 int DRM_MODE_FB_MODIFIERS ; 
 int EINVAL ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int framebuffer_check (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 struct drm_framebuffer* stub1 (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*) ; 

struct drm_framebuffer *
drm_internal_framebuffer_create(struct drm_device *dev,
				const struct drm_mode_fb_cmd2 *r,
				struct drm_file *file_priv)
{
	struct drm_mode_config *config = &dev->mode_config;
	struct drm_framebuffer *fb;
	int ret;

	if (r->flags & ~(DRM_MODE_FB_INTERLACED | DRM_MODE_FB_MODIFIERS)) {
		DRM_DEBUG_KMS("bad framebuffer flags 0x%08x\n", r->flags);
		return ERR_PTR(-EINVAL);
	}

	if ((config->min_width > r->width) || (r->width > config->max_width)) {
		DRM_DEBUG_KMS("bad framebuffer width %d, should be >= %d && <= %d\n",
			  r->width, config->min_width, config->max_width);
		return ERR_PTR(-EINVAL);
	}
	if ((config->min_height > r->height) || (r->height > config->max_height)) {
		DRM_DEBUG_KMS("bad framebuffer height %d, should be >= %d && <= %d\n",
			  r->height, config->min_height, config->max_height);
		return ERR_PTR(-EINVAL);
	}

	if (r->flags & DRM_MODE_FB_MODIFIERS &&
	    !dev->mode_config.allow_fb_modifiers) {
		DRM_DEBUG_KMS("driver does not support fb modifiers\n");
		return ERR_PTR(-EINVAL);
	}

	ret = framebuffer_check(dev, r);
	if (ret)
		return ERR_PTR(ret);

	fb = dev->mode_config.funcs->fb_create(dev, file_priv, r);
	if (IS_ERR(fb)) {
		DRM_DEBUG_KMS("could not create framebuffer\n");
		return fb;
	}

	return fb;
}