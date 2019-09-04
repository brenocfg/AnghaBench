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
 scalar_t__ i915_gem_object_is_active (struct drm_i915_gem_object*) ; 

__attribute__((used)) static char get_active_flag(struct drm_i915_gem_object *obj)
{
	return i915_gem_object_is_active(obj) ? '*' : ' ';
}