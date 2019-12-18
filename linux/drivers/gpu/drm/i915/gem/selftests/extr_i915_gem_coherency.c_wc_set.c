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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_MAP_WC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_lock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/ * i915_gem_object_pin_map (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_wc_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 

__attribute__((used)) static int wc_set(struct drm_i915_gem_object *obj,
		  unsigned long offset,
		  u32 v)
{
	u32 *map;
	int err;

	i915_gem_object_lock(obj);
	err = i915_gem_object_set_to_wc_domain(obj, true);
	i915_gem_object_unlock(obj);
	if (err)
		return err;

	map = i915_gem_object_pin_map(obj, I915_MAP_WC);
	if (IS_ERR(map))
		return PTR_ERR(map);

	map[offset / sizeof(*map)] = v;
	i915_gem_object_unpin_map(obj);

	return 0;
}