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
struct drm_framebuffer {int dummy; } ;
struct intel_framebuffer {struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int intel_framebuffer_init (struct intel_framebuffer*,struct drm_i915_gem_object*,struct drm_mode_fb_cmd2*) ; 
 int /*<<< orphan*/  kfree (struct intel_framebuffer*) ; 
 struct intel_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_framebuffer *
intel_framebuffer_create(struct drm_i915_gem_object *obj,
			 struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct intel_framebuffer *intel_fb;
	int ret;

	intel_fb = kzalloc(sizeof(*intel_fb), GFP_KERNEL);
	if (!intel_fb)
		return ERR_PTR(-ENOMEM);

	ret = intel_framebuffer_init(intel_fb, obj, mode_cmd);
	if (ret)
		goto err;

	return &intel_fb->base;

err:
	kfree(intel_fb);
	return ERR_PTR(ret);
}