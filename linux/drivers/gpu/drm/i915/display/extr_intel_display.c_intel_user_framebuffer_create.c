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
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_i915_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 struct drm_framebuffer* intel_framebuffer_create (struct drm_i915_gem_object*,struct drm_mode_fb_cmd2*) ; 

__attribute__((used)) static struct drm_framebuffer *
intel_user_framebuffer_create(struct drm_device *dev,
			      struct drm_file *filp,
			      const struct drm_mode_fb_cmd2 *user_mode_cmd)
{
	struct drm_framebuffer *fb;
	struct drm_i915_gem_object *obj;
	struct drm_mode_fb_cmd2 mode_cmd = *user_mode_cmd;

	obj = i915_gem_object_lookup(filp, mode_cmd.handles[0]);
	if (!obj)
		return ERR_PTR(-ENOENT);

	fb = intel_framebuffer_create(obj, &mode_cmd);
	i915_gem_object_put(obj);

	return fb;
}