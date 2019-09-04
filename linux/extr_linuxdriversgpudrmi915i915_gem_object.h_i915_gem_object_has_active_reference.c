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
struct drm_i915_gem_object {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_BO_ACTIVE_REF ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
i915_gem_object_has_active_reference(const struct drm_i915_gem_object *obj)
{
	return test_bit(I915_BO_ACTIVE_REF, &obj->flags);
}