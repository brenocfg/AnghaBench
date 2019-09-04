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
struct intel_framebuffer {int dummy; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  framebuffer_references; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  kfree (struct intel_framebuffer*) ; 
 struct intel_framebuffer* to_intel_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void intel_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct intel_framebuffer *intel_fb = to_intel_framebuffer(fb);
	struct drm_i915_gem_object *obj = intel_fb_obj(fb);

	drm_framebuffer_cleanup(fb);

	i915_gem_object_lock(obj);
	WARN_ON(!obj->framebuffer_references--);
	i915_gem_object_unlock(obj);

	i915_gem_object_put(obj);

	kfree(intel_fb);
}