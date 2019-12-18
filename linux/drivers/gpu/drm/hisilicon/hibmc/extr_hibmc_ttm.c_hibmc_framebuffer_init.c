#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hibmc_framebuffer {int /*<<< orphan*/  fb; struct drm_gem_object* obj; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOMEM ; 
 struct hibmc_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_framebuffer_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,int /*<<< orphan*/ *,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  hibmc_fb_funcs ; 
 int /*<<< orphan*/  kfree (struct hibmc_framebuffer*) ; 
 struct hibmc_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct hibmc_framebuffer *
hibmc_framebuffer_init(struct drm_device *dev,
		       const struct drm_mode_fb_cmd2 *mode_cmd,
		       struct drm_gem_object *obj)
{
	struct hibmc_framebuffer *hibmc_fb;
	int ret;

	hibmc_fb = kzalloc(sizeof(*hibmc_fb), GFP_KERNEL);
	if (!hibmc_fb) {
		DRM_ERROR("failed to allocate hibmc_fb\n");
		return ERR_PTR(-ENOMEM);
	}

	drm_helper_mode_fill_fb_struct(dev, &hibmc_fb->fb, mode_cmd);
	hibmc_fb->obj = obj;
	ret = drm_framebuffer_init(dev, &hibmc_fb->fb, &hibmc_fb_funcs);
	if (ret) {
		DRM_ERROR("drm_framebuffer_init failed: %d\n", ret);
		kfree(hibmc_fb);
		return ERR_PTR(ret);
	}

	return hibmc_fb;
}