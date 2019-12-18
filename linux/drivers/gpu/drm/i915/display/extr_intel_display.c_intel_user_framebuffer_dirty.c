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
struct drm_i915_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORIGIN_DIRTYFB ; 
 int /*<<< orphan*/  i915_gem_object_flush_if_display (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* intel_fb_obj (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_frontbuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int intel_user_framebuffer_dirty(struct drm_framebuffer *fb,
					struct drm_file *file,
					unsigned flags, unsigned color,
					struct drm_clip_rect *clips,
					unsigned num_clips)
{
	struct drm_i915_gem_object *obj = intel_fb_obj(fb);

	i915_gem_object_flush_if_display(obj);
	intel_frontbuffer_flush(to_intel_frontbuffer(fb), ORIGIN_DIRTYFB);

	return 0;
}