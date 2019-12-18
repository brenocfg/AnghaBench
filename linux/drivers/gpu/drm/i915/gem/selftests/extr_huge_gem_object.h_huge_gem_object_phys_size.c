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
struct drm_i915_gem_object {int /*<<< orphan*/  scratch; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline phys_addr_t
huge_gem_object_phys_size(struct drm_i915_gem_object *obj)
{
	return obj->scratch;
}