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

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 

__attribute__((used)) static inline void
i915_gem_object_finish_access(struct drm_i915_gem_object *obj)
{
	i915_gem_object_unpin_pages(obj);
	i915_gem_object_unlock(obj);
}